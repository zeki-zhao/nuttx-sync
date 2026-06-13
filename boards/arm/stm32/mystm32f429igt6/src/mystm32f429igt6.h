/****************************************************************************
 * boards/arm/stm32/stm32f429i-disco/src/stm32f429i-disco.h
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

#ifndef __BOARDS_ARM_STM32_MYSTM32F429IGT6_SRC_STM32F429I_DISCO_H
#define __BOARDS_ARM_STM32_MYSTM32F429IGT6_SRC_STM32F429I_DISCO_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <stdint.h>


#include <arch/stm32/chip.h>

#include "stm32_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

/* Color definitions for console output */
#define COLOR_RED   "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RESET "\033[0m\n"


#define HAVE_PROC       
#define HAVE_USBDEV     
#define HAVE_USBHOST    
#define HAVE_USBMONITOR 

#undef  SDIO_MINOR     /* Any minor number, default 0 */
#define SDIO_SLOTNO 0  /* Only one slot */


#  if !defined(CONFIG_NSH_MMCSDSLOTNO)
#    define CONFIG_NSH_MMCSDSLOTNO SDIO_SLOTNO
#  elif CONFIG_NSH_MMCSDSLOTNO != 0
#    warning "Only one MMC/SD slot, slot 0"
#    undef CONFIG_NSH_MMCSDSLOTNO
#    define CONFIG_NSH_MMCSDSLOTNO SDIO_SLOTNO
#  endif

#  if defined(CONFIG_NSH_MMCSDMINOR)
#    define SDIO_MINOR CONFIG_NSH_MMCSDMINOR
#  else
#    define SDIO_MINOR 0
#  endif

/* Can't support USB host or device features if USB OTG HS is not enabled */

#ifndef CONFIG_STM32_OTGHS
#  undef HAVE_USBDEV
#  undef HAVE_USBHOST
#endif

/* Can't support USB device monitor if USB device is not enabled */

#ifndef CONFIG_USBDEV
#  undef HAVE_USBDEV
#endif

/* Can't support USB host is USB host is not enabled */

#ifndef CONFIG_USBHOST
#  undef HAVE_USBHOST
#endif

/* Check if we should enable the USB monitor before starting NSH */

#ifndef CONFIG_USBMONITOR
#  undef HAVE_USBMONITOR
#endif

#ifndef HAVE_USBDEV
#  undef CONFIG_USBDEV_TRACE
#endif

#ifndef HAVE_USBHOST
#  undef CONFIG_USBHOST_TRACE
#endif

#if !defined(CONFIG_USBDEV_TRACE) && !defined(CONFIG_USBHOST_TRACE)
#  undef HAVE_USBMONITOR
#endif

/* Check if we have the procfs file system */

#if !defined(CONFIG_FS_PROCFS)
#  undef HAVE_PROC
#endif

#if defined(HAVE_PROC) && defined(CONFIG_DISABLE_MOUNTPOINT)
#  warning Mountpoints disabled.  No procfs support
#  undef HAVE_PROC
#endif

/* How many SPI modules does this chip support? */

#if STM32_NSPI < 1
#  undef CONFIG_STM32_SPI1
#  undef CONFIG_STM32_SPI2
#  undef CONFIG_STM32_SPI3
#elif STM32_NSPI < 2
#  undef CONFIG_STM32_SPI2
#  undef CONFIG_STM32_SPI3
#elif STM32_NSPI < 3
#  undef CONFIG_STM32_SPI3
#endif


                  

/* BUTTONS -- NOTE that all have EXTI interrupts configured */

#define MIN_IRQBUTTON   BUTTON_USER
#define MAX_IRQBUTTON   BUTTON_USER
#define NUM_IRQBUTTONS  1

#define GPIO_BTN_USER   (GPIO_INPUT|GPIO_FLOAT|GPIO_EXTI|GPIO_PORTA|GPIO_PIN0)

/* PWM
 *
 * The STM32F429 Discovery has no real on-board PWM devices, but the board
 * can be configured to output a pulse train using TIM4 CH2 on PD13.
 */

#define STM32F429I_DISCO_PWMTIMER   4
#define STM32F429I_DISCO_PWMCHANNEL 2

/* SPI chip selects */

#define GPIO_CS_FLASH   (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|\
                         GPIO_OUTPUT_SET|GPIO_PORTI|GPIO_PIN8)
#define GPIO_LCD_ENABLE (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_50MHz|\
                         GPIO_OUTPUT_CLEAR|GPIO_PORTF|GPIO_PIN10)

/* W25Q128 partition layout (128 Mbit = 16 MB SPI NOR flash) */

#define PRIMARY_OFFSET    0x000000
#define PRIMARY_SIZE      0x100000                  /* 1 MB */

#define SECONDARY_OFFSET  (PRIMARY_OFFSET + PRIMARY_SIZE)
#define SECONDARY_SIZE    0x100000                  /* 1 MB */

#define RECOVERY_OFFSET   (SECONDARY_OFFSET + SECONDARY_SIZE)
#define RECOVERY_SIZE     0x100000                  /* 1 MB */

#define CONFIG_OFFSET     (RECOVERY_OFFSET + RECOVERY_SIZE)
#define CONFIG_SIZE       0x10000                   /* 64 KB */

#define ASSETS_OFFSET     (CONFIG_OFFSET + CONFIG_SIZE)
#define ASSETS_SIZE       (0x1000000 - ASSETS_OFFSET)  /* Remainder ~12.94 MB */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************

 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Public Function Prototypes
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

int stm32_bringup(void);

// #ifdef CONFIG_STM32_SDIO //!defined(CONFIG_DISABLE_MOUNTPOINT) &&
int stm32_sdio_initialize(void);
// #endif


/****************************************************************************
 * Name: stm32_spidev_initialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the stm32f429i-disco
 *   board.
 *
 ****************************************************************************/

void weak_function stm32_spidev_initialize(void);

#ifdef CONFIG_MY_LED
int board_myled_initialize(void);
#endif

#ifdef CONFIG_MY_TOUCH
void board_touch_initialize(void);
#endif

void board_buzzer_init(void);
void board_buzzer_start(int half_period_us);
void board_buzzer_stop(void);
void board_buzzer_set_period(int half_period_us);
int  board_note_to_hp(const char *name);

/****************************************************************************
 * Name: stm32_usbinitialize
 *
 * Description:
 *   Called from stm32_usbinitialize very early in inialization to setup USB-
 *   related GPIO pins for the STM32F429Discovery board.
 *
 ****************************************************************************/

#ifdef CONFIG_STM32_OTGHS
void weak_function stm32_usbinitialize(void);
#endif

/****************************************************************************
 * Name: stm32_usbhost_initialize
 *
 * Description:
 *   Called at application startup time to initialize the USB host
 *   functionality. This function will start a thread that will monitor for
 *   device connection/disconnection events.
 *
 ****************************************************************************/

#if defined(CONFIG_STM32_OTGHS) && defined(CONFIG_USBHOST)
int stm32_usbhost_initialize(void);
#endif



/****************************************************************************
 * Name: stm32_sdram_initialize
 *
 * Description:
 *   Called from stm32_bringup to initialize external SDRAM access.
 *
 ****************************************************************************/

#ifdef CONFIG_STM32_FMC
void stm32_sdram_initialize(void);
#endif

/****************************************************************************
 * Name: stm32_ledpminitialize
 *
 * Description:
 *   Enable logic to use the LEDs on the STM32F429Discovery to support
 *   power management testing
 *
 ****************************************************************************/

#ifdef CONFIG_PM
void stm32_ledpminitialize(void);
#endif

/****************************************************************************
 * Name: stm32_pmbuttons
 *
 * Description:
 *   Configure the user button of the STM32F429I-DISCO board as EXTI,
 *   so it is able to wakeup the MCU from the PM_STANDBY mode
 *
 ****************************************************************************/

#if defined(CONFIG_PM) && defined(CONFIG_ARCH_IDLE_CUSTOM) && \
    defined(CONFIG_PM_BUTTONS)
void stm32_pmbuttons(void);
#endif


/****************************************************************************
 * Name: stm32_spi1initialize
 *
 * Description:
 *   Initialize the selected SPI port.
 *   As long as the method stm32_spibus_initialize() recognized the
 *   initialized state of the spi device by the spi enable flag of the cr1
 *   register, it isn't safe to disable the spi device outside of the nuttx
 *   spi interface structure. But this has to be done as long as the nuttx
 *   spi interface doesn't support bidirectional data transfer for multiple
 *   devices share one spi bus. This wrapper does nothing else than store
 *   the initialized state of the spi device after the first initializing
 *   and should be used by each driver who shares the spi5 bus.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Valid SPI device structure reference on success; a NULL on failure
 *
 ****************************************************************************/

#ifdef CONFIG_STM32_SPI1
struct spi_dev_s *stm32_spi1initialize(void);
#endif


/****************************************************************************
 * Name: stm32_pwm_setup
 *
 * Description:
 *   Initialize PWM and register the PWM device.
 *
 ****************************************************************************/

#ifdef CONFIG_PWM
int stm32_pwm_setup(void);
#endif

/****************************************************************************
 * Name: stm32_adc_setup
 *
 * Description:
 *   Initialize ADC and register the ADC device.
 *
 ****************************************************************************/

#ifdef CONFIG_ADC
int stm32_adc_setup(void);
#endif




#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_ARM_STM32_STM32F429I_DISCO_SRC_STM32F429I_DISCO_H */
