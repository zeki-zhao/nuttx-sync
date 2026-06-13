/****************************************************************************
 * boards/arm/stm32/stm32f429i-disco/src/stm32_bringup.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdbool.h>
#include <stdio.h>
#include <debug.h>
#include <errno.h>
#include <sys/stat.h>
#include <nuttx/board.h>
#include <nuttx/fs/fs.h>
#include <nuttx/kmalloc.h>
#include <nuttx/spi/spi.h>

#include "mystm32f429igt6.h"

#ifdef CONFIG_FS_FAT
#  include <arch/board/board_paths.h>
#endif

#ifdef CONFIG_VIDEO_FB
#  include <nuttx/video/fb.h>
#endif

#ifdef CONFIG_STM32_OTGHS
#  include "stm32_usbhost.h"
#endif

#ifdef CONFIG_INPUT_BUTTONS_LOWER
#  include <nuttx/input/buttons.h>
#endif

#ifdef CONFIG_MTD
# include <nuttx/mtd/mtd.h>
# include <fcntl.h>
#endif

/****************************************************************************
 * Public Data
 ****************************************************************************/


/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y :
 *     Called from board_late_initialize().
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y && CONFIG_BOARDCTL=y :
 *     Called from the NSH library
 *
 ****************************************************************************/

int stm32_bringup(void)
{
    int ret;
#if !defined(CONFIG_NXBOOT_BOOTLOADER)
    printf(COLOR_GREEN "Hello,Zeki\nWelcome to Nuttx of STM32F429IGT6" COLOR_RESET);
#endif

#if !defined(CONFIG_NXBOOT_BOOTLOADER)
    /* Initialize the SDIO block driver */

    ret = stm32_sdio_initialize();
    if (ret != OK){
        syslog(LOG_DEBUG,"in %s:%d\n",__func__,__LINE__);
        ferr("ERROR: Failed to initialize MMC/SD driver: %d\n", ret);
        return ret;
    }else{
#if defined(CONFIG_FS_FAT) && !defined(CONFIG_DISABLE_MOUNTPOINT)
        /* Mount the SD card to /mnt/sd if FATFS is enabled */
        char devpath[32];
        snprintf(devpath, sizeof(devpath), "/dev/mmcsd%d", SDIO_MINOR);
        mkdir("/mnt/sd", 0777);
        ret = nx_mount(devpath, "/mnt/sd", "vfat", 0, NULL);
        if (ret < 0){
            syslog(LOG_ERR,"ERROR: Failed to mount SD card to /mnt/sd: %d\n", ret);
        }else{
            /* Ensure required data directories exist on SD card */
            mkdir(SD_STATE_DIR, 0777);
            mkdir(SD_LOG_DIR, 0777);
            mkdir(SD_CONFIG_DIR, 0777);
            mkdir(SD_FIRMWARE_DIR, 0777);
        }
#else
        syslog(LOG_WARN, "WARNING: SDIO device registered but FATFS not enabled, "
                     "SD card not mounted\n");
#endif
    }
#endif

#if defined (CONFIG_MY_LED)
    board_myled_initialize();
#endif

#if defined (CONFIG_MY_TOUCH)
    board_touch_initialize();
#endif

#if defined (CONFIG_MY_BUZZER)
    board_buzzer_init();
#endif


#ifdef HAVE_PROC
  /* mount the proc filesystem */
    ret = nx_mount(NULL, CONFIG_NSH_PROC_MOUNTPOINT, "procfs", 0, NULL);
    if (ret < 0)
    {
        syslog(LOG_ERR,
                "ERROR: Failed to mount the PROC filesystem: %d\n", ret);
        return ret;
    }
#endif

  /* Configure SPI-based devices */

#if defined(CONFIG_STM32_SPI1)
  struct spi_dev_s *spi;
  /* Get the SPI port */
 #endif

#if defined(CONFIG_MTD)
    struct mtd_dev_s *mtd;
    struct mtd_geometry_s geo;
#endif

#if defined(CONFIG_STM32_SPI1)
    spi = stm32_spi1initialize();
    if (!spi){
        syslog(LOG_ERR, "ERROR: Failed to initialize SPI port 1\n");
        return -ENODEV;
    }

#if defined(CONFIG_MTD) && defined(CONFIG_MTD_W25)
    /* Quick SPI1 communication test: read JEDEC ID from W25Q directly */
    mtd = w25_initialize(spi);
    if (!mtd){
        syslog(LOG_ERR, "ERROR: SPI1 communication test FAILED - "
                        "w25_initialize returned NULL (no JEDEC ID match)\n");
    }else{
        /* Read geometry and print flash info */

        ret = mtd->ioctl(mtd, MTDIOC_GEOMETRY,
                        (unsigned long)((uintptr_t)&geo));
        if (ret < 0){
            syslog(LOG_ERR, "ERROR: Failed to get W25 geometry: %d\n", ret);
        }

        /* Parse flash partitions using mtd_partition() */
        FAR struct mtd_dev_s *primary = mtd_partition(mtd,
                    PRIMARY_OFFSET / geo.blocksize,
                    PRIMARY_SIZE   / geo.blocksize);

        FAR struct mtd_dev_s *secondary = mtd_partition(mtd,
                    SECONDARY_OFFSET / geo.blocksize,
                    SECONDARY_SIZE   / geo.blocksize);

        FAR struct mtd_dev_s *recovery = mtd_partition(mtd,
                    RECOVERY_OFFSET / geo.blocksize,
                    RECOVERY_SIZE   / geo.blocksize);

        FAR struct mtd_dev_s *config = mtd_partition(mtd,
                    CONFIG_OFFSET / geo.blocksize,
                    CONFIG_SIZE   / geo.blocksize);

#if defined(CONFIG_MTD_PARTITION_NAMES)
        mtd_setpartitionname(primary, "primary");
        mtd_setpartitionname(secondary, "secondary");
        mtd_setpartitionname(recovery, "recovery");
        mtd_setpartitionname(config, "config");
#endif

#if defined(CONFIG_BOOT_NXBOOT)
        /* Register OTA partitions for nxboot */
        ret = register_mtddriver(CONFIG_NXBOOT_PRIMARY_SLOT_PATH, primary, 0755, NULL);
        if (ret < 0)
            syslog(LOG_ERR, "ERROR: Failed to register %s: %d\n",
                    CONFIG_NXBOOT_PRIMARY_SLOT_PATH, ret);

        ret = register_mtddriver(CONFIG_NXBOOT_SECONDARY_SLOT_PATH, secondary, 0755, NULL);
        if (ret < 0)
            syslog(LOG_ERR, "ERROR: Failed to register %s: %d\n",
                    CONFIG_NXBOOT_SECONDARY_SLOT_PATH, ret);

        ret = register_mtddriver(CONFIG_NXBOOT_TERTIARY_SLOT_PATH, recovery, 0755, NULL);
        if (ret < 0)
            syslog(LOG_ERR, "ERROR: Failed to register %s: %d\n",
                    CONFIG_NXBOOT_TERTIARY_SLOT_PATH, ret);
                    
#endif /* CONFIG_BOOT_NXBOOT */
        
#if defined(CONFIG_FS_LITTLEFS)
        FAR struct mtd_dev_s *assets = mtd_partition(mtd,
                        ASSETS_OFFSET / geo.blocksize,
                        ASSETS_SIZE   / geo.blocksize);

        ret = register_mtddriver("/dev/assets", assets, 0755, NULL);
        if (ret < 0){
            syslog(LOG_ERR, "ERROR: Failed to register /dev/assets: %d\n", ret);
        }else{
            mkdir("/mnt/assets", 0777);
            ret = nx_mount("/dev/assets", "/mnt/assets", "littlefs", 0,
                            "autoformat");
            if (ret < 0){
                syslog(LOG_ERR, "ERROR: Failed to mount littlefs: %d\n", ret);
            }
        }
#endif /* CONFIG_FS_LITTLEFS */
    }

#endif /* CONFIG_MTD */
#endif /* CONFIG_STM32_SPI1 */


#ifdef CONFIG_VIDEO_FB
  /* Initialize and register the framebuffer driver */

    ret = fb_register(0, 0);
    if (ret < 0){
        syslog(LOG_ERR, "ERROR: fb_register() failed: %d\n", ret);
    }
#endif


#ifdef HAVE_USBHOST
    /* Initialize USB host operation.  stm32_usbhost_initialize() starts a
    * thread will monitor for USB connection and disconnection events.
    */
    ret = stm32_usbhost_initialize();
    if (ret != OK){
        syslog(LOG_ERR, "ERROR: Failed to initialize USB host: %d\n", ret);
        return ret;
    }
#endif


#ifdef CONFIG_INPUT_BUTTONS_LOWER
  /* Register the BUTTON driver */

    ret = btn_lower_initialize("/dev/buttons");
    if (ret < 0){
        syslog(LOG_ERR, "ERROR: btn_lower_initialize() failed: %d\n", ret);
    }
#endif /* CONFIG_INPUT_BUTTONS_LOWER */

#ifdef CONFIG_PWM
  /* Initialize PWM and register the PWM device. */

    ret = stm32_pwm_setup();
    if (ret < 0){
        syslog(LOG_ERR, "ERROR: stm32_pwm_setup() failed: %d\n", ret);
    }
#endif


#ifdef CONFIG_ADC
  /* Initialize ADC and register the ADC device. */

    ret = stm32_adc_setup();
    if (ret < 0){
        syslog(LOG_ERR, "ERROR: stm32_adc_setup() failed: %d\n", ret);
    }
#endif

    return OK;
}
