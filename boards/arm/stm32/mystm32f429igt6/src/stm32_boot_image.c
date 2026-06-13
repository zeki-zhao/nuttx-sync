/****************************************************************************
 * boards/arm/stm32/mystm32f429igt6/src/stm32_boot_image.c
 *
 * SPDX-License-Identifier: Apache-2.0
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

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <syslog.h>
#include <sys/boardctl.h>

#include <nuttx/irq.h>
#include <nuttx/progmem.h>
#include <nuttx/arch.h>
#include <arch/barriers.h>

#include "arm_internal.h"
#include "chip.h"
#include "stm32_gpio.h"
#include "hardware/stm32f40xxx_rcc.h"
#include "hardware/stm32f40xxx_gpio.h"
#include "nvic.h"
#include <arch/board/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define APP_FLASH_ADDR  0x08020000
#define BUF_SIZE        256

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* NXBOOT image header (offset 0 in the MTD partition) */

struct nxboot_hdr_version {
    uint8_t major;
    uint8_t minor;
};

struct nxboot_img_version {
    uint16_t major;
    uint16_t minor;
    uint16_t patch;
    char     pre_release[94];
};

struct nxboot_img_header {
    uint32_t                    magic;
    struct nxboot_hdr_version   hdr_version;
    uint16_t                    header_size;
    uint32_t                    crc;
    uint32_t                    size;
    uint64_t                    identifier;
    uint32_t                    extd_hdr_ptr;
    struct nxboot_img_version   img_version;
};

/* ARM vector table (first 8 bytes of firmware, after nxboot header) */

struct arm_vector_table {
    uint32_t spr;   /* Stack pointer on reset */
    uint32_t reset; /* Reset handler address */
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static void systick_disable(void)
{
    putreg32(0, NVIC_SYSTICK_CTRL);
    putreg32(0, NVIC_SYSTICK_RELOAD);
    putreg32(0, NVIC_SYSTICK_CURRENT);
}

static void cleanup_arm_nvic(void)
{
    int i;

    UP_ISB();
    cpsid();

    for (i = 0; i < NR_IRQS; i += 32) {
        putreg32(0xffffffff, NVIC_IRQ_CLEAR(i));
    }

    for (i = 0; i < NR_IRQS; i += 32) {
        putreg32(0xffffffff, NVIC_IRQ_CLRPEND(i));
    }
}

/****************************************************************************
 * Name: board_force_revert_check
 *
 * Description:
 *   Check if the user button is held at boot to force a revert to
 *   the recovery image. Returns true if the button (PA0, active low)
 *   is pressed.
 *
 ****************************************************************************/

bool board_force_revert_check(void)
{
    // int i;

    // /* Configure PA0 as input with pull-up to ensure stable reading */
    // stm32_configgpio(GPIO_INPUT | GPIO_PULLUP | GPIO_PORTA | GPIO_PIN0);

    // /* Small delay for the pin state to settle */
    // for (i = 0; i < 10000; i++);

    // /* Active low: read twice with debounce */
    // if ((getreg32(STM32_GPIOA_IDR) & GPIO_PIN0) == 0)
    // {
    //     for (i = 0; i < 10000; i++);
    //     if ((getreg32(STM32_GPIOA_IDR) & GPIO_PIN0) == 0)
    //     {
    //         return true;
    //     }
    // }

    return false;
}

/****************************************************************************
 * Name: board_indicate
 *
 * Description:
 *   Override the weak function from nxboot. Uses the red LED (PH10) to
 *   signal bootloader state:
 *     startup_msg        → LED on
 *     recovery_revert    → slow blink 3× (200ms)
 *     update_from_update → fast blink 5× (80ms)
 *     found_bootable     → LED off
 *     error states       → fast blink forever (system hangs)
 *     progress_end       → LED off
 *
 ****************************************************************************/

void board_indicate(int msg)
{
    static bool configured = false;

    if (!configured)
    {
        stm32_configgpio(LED_STATUS);
        configured = true;
    }

    switch (msg)
    {
        case 0:  /* startup_msg */
            stm32_gpiowrite(LED_STATUS, true);
            break;

        case 7:  /* recovery_revert */
            for (int i = 0; i < 3; i++)
            {
                stm32_gpiowrite(LED_STATUS, true);
                up_mdelay(200);
                stm32_gpiowrite(LED_STATUS, false);
                up_mdelay(200);
            }
            break;

        case 9:  /* update_from_update */
            for (int i = 0; i < 5; i++)
            {
                stm32_gpiowrite(LED_STATUS, true);
                up_mdelay(80);
                stm32_gpiowrite(LED_STATUS, false);
                up_mdelay(80);
            }
            break;

        case 3:  /* found_bootable_image */
            stm32_gpiowrite(BLING_LED_R, false);
            break;

        case 4:  /* no_bootable_image */
        case 5:  /* boardioc_image_boot_fail */
        case 14: /* recovery_invalid */
        case 15: /* update_failed */
            while (1)
            {
                stm32_gpiowrite(LED_STATUS, true);
                up_mdelay(100);
                stm32_gpiowrite(LED_STATUS, false);
                up_mdelay(100);
            }
            break;

        default:
            if (msg < 0)
            {
                /* progress_end */
                stm32_gpiowrite(LED_STATUS, false);
            }
            break;
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_boot_image
 *
 * Description:
 *   Boot the application firmware from the given flash partition.
 *   Copies the firmware from the MTD partition to internal flash
 *   at APP_FLASH_ADDR, then disables interrupts and jumps to the
 *   application's reset handler.
 *
 ****************************************************************************/

#ifdef CONFIG_BOARDCTL_BOOT_IMAGE
int board_boot_image(FAR const char *path, uint32_t hdr_size)
{
    int fd;
    int ret;
    ssize_t nread;
    off_t flash_off;
    size_t remaining;
    size_t chunk;
    uint32_t app_size;
    uint32_t page_addr;
    size_t page_size;
    int page;
    bool need_update;
    uint8_t buf[BUF_SIZE] __attribute__((aligned(4)));
    struct nxboot_img_header hdr;
    struct arm_vector_table vt;

    /* Open the MTD partition */

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        syslog(LOG_ERR, "Failed to open %s: %d\n", path, errno);
        return -errno;
    }

    /* Read the nxboot header to get firmware size */

    nread = read(fd, &hdr, sizeof(hdr));
    if (nread != sizeof(hdr)) {
        syslog(LOG_ERR, "Failed to read image header: %zd\n", nread);
        close(fd);
        return -EIO;
    }

    app_size = hdr.size;
    syslog(LOG_INFO, "Firmware size: %lu bytes\n", (unsigned long)app_size);

    if (hdr_size < sizeof(hdr) || hdr_size != hdr.header_size) {
        syslog(LOG_ERR, "Header size mismatch: param=%u header_field=%u\n",
               hdr_size, hdr.header_size);
        close(fd);
        return -EINVAL;
    }

    /* Seek past the header to firmware data */

    ret = lseek(fd, hdr_size, SEEK_SET);
    if (ret < 0) {
        close(fd);
        return -errno;
    }

    /* Compare with existing firmware in internal flash to avoid
     * unnecessary erase/write on every boot.
     */

    need_update = false;
    flash_off   = 0;
    remaining   = app_size;

    while (remaining > 0 && !need_update) {
        chunk = remaining;
        if (chunk > sizeof(buf)) {
            chunk = sizeof(buf);
        }

        if (chunk & 1) {
            chunk--;
        }

        nread = read(fd, buf, chunk);
        if (nread <= 0) {
            break;
        }

        if (memcmp(buf, (const void *)(APP_FLASH_ADDR + flash_off),
                   nread) != 0) {
            need_update = true;
        }

        flash_off += nread;
        remaining -= nread;
    }

    if (need_update) {
        syslog(LOG_INFO, "Firmware changed, erasing and writing...\n");

        ret = lseek(fd, hdr_size, SEEK_SET);
        if (ret < 0) {
            close(fd);
            return -errno;
        }

        /* Erase internal flash sectors that contain the app region */

        page_addr = APP_FLASH_ADDR;
        while (page_addr < APP_FLASH_ADDR + app_size) {
            page = up_progmem_getpage(page_addr);
            if (page < 0) {
                syslog(LOG_ERR, "Invalid flash page for 0x%x\n", page_addr);
                close(fd);
                return -EINVAL;
            }

            page_size = up_progmem_pagesize(page);
            syslog(LOG_INFO, "Erasing sector %d (0x%x, %lu bytes)\n",
                   page, page_addr, (unsigned long)page_size);

            ret = up_progmem_eraseblock(page);
            if (ret < 0) {
                syslog(LOG_ERR, "Erase sector %d failed: %d\n", page, ret);
                close(fd);
                return ret;
            }

            page_addr += page_size;
        }

        /* Copy firmware from MTD to internal flash */

        flash_off = 0;
        remaining = app_size;

        while (remaining > 0) {
            chunk = remaining;
            if (chunk > sizeof(buf)) {
                chunk = sizeof(buf);
            }

            /* Flash requires half-word writes; ensure even count */

            if (chunk & 1) {
                chunk--;
            }

            nread = read(fd, buf, chunk);
            if (nread <= 0) {
                syslog(LOG_ERR, "Read failed at offset 0x%lx: %zd\n",
                       (long)flash_off, nread);
                close(fd);
                return -EIO;
            }

            ret = up_progmem_write(APP_FLASH_ADDR + flash_off, buf, nread);
            if (ret < 0) {
                syslog(LOG_ERR, "Flash write failed at 0x%x: %d\n",
                       APP_FLASH_ADDR + flash_off, ret);
                close(fd);
                return ret;
            }

            flash_off += nread;
            remaining -= nread;
        }

        syslog(LOG_INFO, "Firmware copied to 0x%x (%ld bytes)\n",
               APP_FLASH_ADDR, (long)flash_off);
    } else {
        syslog(LOG_INFO, "Firmware already up to date\n");
    }

    close(fd);

    /* Verify vector table — use volatile read to guarantee actual flash
     * access.
     */

    {
        volatile uint32_t *vt_base = (volatile uint32_t *)APP_FLASH_ADDR;
        vt.spr   = vt_base[0];
        vt.reset = vt_base[1];
    }

    if (vt.reset == 0 || vt.reset == 0xffffffff ||
        vt.spr == 0 || vt.spr == 0xffffffff) {
        syslog(LOG_ERR, "Invalid vector table: spr=0x%lx reset=0x%lx\n",
               (unsigned long)vt.spr, (unsigned long)vt.reset);
        return -EINVAL;
    }

    if (!(vt.reset & 1)) {
        syslog(LOG_ERR, "Reset vector not Thumb (bit0=0): 0x%lx\n",
               (unsigned long)vt.reset);
        return -EINVAL;
    }

    syslog(LOG_INFO, "Vector table OK: sp=0x%lx reset=0x%lx\n",
           (unsigned long)vt.spr, (unsigned long)vt.reset);

    /* Invalidate I-Cache via architectural ICIALLU register */

    putreg32(0, NVIC_ICIALLU);

    /* Disable SysTick */

    systick_disable();

    /* Disable and clear all NVIC interrupts */

    cleanup_arm_nvic();

    up_mdelay(10);

    /* Set MSP and jump to app reset handler.
     * vt.reset has bit 0 = 1 for Thumb mode; BX strips it before jumping.
     * control=0 means main stack (not process stack).
     */

    __asm__ __volatile__
    (
        "msr msp, %0\n"
        "msr CONTROL, %1\n"
        "isb\n"
        "bx %2\n"
        :
        : "r" (vt.spr),
            "r" (0),
            "r" (vt.reset)
        : "memory"
    );

    /* Never reached */

    return 0;
}
#endif

/****************************************************************************
 * Name: board_reset_cause
 *
 * Description:
 *   Get the cause of the last board reset by reading the RCC_CSR register.
 *
 ****************************************************************************/

#ifdef CONFIG_BOARDCTL_RESET_CAUSE
int board_reset_cause(FAR struct boardioc_reset_cause_s *cause)
{
    uint32_t csr = getreg32(STM32_RCC_CSR);

    if (csr & RCC_CSR_SFTRSTF) {
        cause->cause = BOARDIOC_RESETCAUSE_CPU_SOFT;
    } else if (csr & RCC_CSR_IWDGRSTF) {
        cause->cause = BOARDIOC_RESETCAUSE_CPU_RWDT;
    } else if (csr & RCC_CSR_WWDGRSTF) {
        cause->cause = BOARDIOC_RESETCAUSE_CPU_MWDT;
    } else if (csr & RCC_CSR_PINRSTF) {
        cause->cause = BOARDIOC_RESETCAUSE_PIN;
    } else if (csr & (RCC_CSR_PORRSTF | RCC_CSR_BORRSTF)) {
        cause->cause = BOARDIOC_RESETCAUSE_SYS_CHIPPOR;
    } else if (csr & RCC_CSR_LPWRRSTF) {
        cause->cause = BOARDIOC_RESETCAUSE_LOWPOWER;
    } else {
        cause->cause = BOARDIOC_RESETCAUSE_UNKOWN;
    }

    cause->flag = 0;

    /* Clear reset flags by writing 1 to RMVF */

    putreg32(RCC_CSR_RMVF, STM32_RCC_CSR);

    return OK;
}
#endif

/****************************************************************************
 * Name: board_reset
 *
 * Description:
 *   Reset the board.  Called by boardctl(BOARDIOC_RESET, ...).
 *
 ****************************************************************************/

#ifdef CONFIG_BOARDCTL_RESET
int board_reset(int status)
{
    up_systemreset();
    return 0;
}
#endif
