/****************************************************************************
 * boards/arm/stm32/mystm32f429igt6/src/stm32_led_indicate.c
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
 * LED indicator shared by bootloader and app.
 *
 * Bootloader: TIM6 ISR-driven (works during busy flash erase/write)
 * App:        Idle-task based on system tick (no interrupt conflicts)
 *
 * board_indicate() / led_indicate_set_mode() set the blink mode;
 * the actual GPIO driving is done either by the TIM6 ISR (bootloader).
 *
 * Blink patterns (tick mask at 100Hz system tick / 50Hz TIM6 tick):
 *   LED_MODE_OFF       → steady off
 *   LED_MODE_ON        → steady on
 *   LED_MODE_VERY_SLOW → ~640ms cycle  (tick & 64)
 *   LED_MODE_SLOW      → ~320ms cycle  (tick & 32)
 *   LED_MODE_FAST      → ~80ms cycle   (tick & 4)
 *   LED_MODE_ERROR     → ~20ms cycle   (tick & 1, rapid flicker)
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <nuttx/clock.h>

#include <arch/board/board.h>

#include "stm32_gpio.h"

#ifdef CONFIG_NXBOOT_BOOTLOADER
#  include "chip.h"
#  include "hardware/stm32_tim.h"
#  include "hardware/stm32f40xxx_rcc.h"
#  include "arm_internal.h"
#  include "nvic.h"
#endif


/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/* TIM6 clock is 2 * APB1 = 84MHz (see board.h STM32_APB1_TIM6_CLKIN).
 * PSC = 8400 → 84MHz / 8400 = 10kHz
 * ARR = 200  → 10kHz / 200 = 50Hz (20ms per ISR tick)
 * Only used in bootloader build.
 */

#ifdef CONFIG_NXBOOT_BOOTLOADER
#  define LED_TIM_PSC         8399
#  define LED_TIM_ARR         199
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

static int  g_led_mode        = LED_MODE_OFF;

void board_autoled_off(int led);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

#ifdef CONFIG_NXBOOT_BOOTLOADER
static int led_tim6_isr(int irq, void *context, void *arg)
{
    static uint32_t tick = 0;
    static bool last_on  = false;
    bool on;

    /* Clear update interrupt flag */
    putreg32(0, STM32_TIM6_SR);

    switch (g_led_mode)
    {
        case LED_MODE_OFF:       on = false;           break;
        case LED_MODE_ON:        on = true;            break;
        case LED_MODE_VERY_SLOW: on = (tick & 32) != 0; break;
        case LED_MODE_SLOW:      on = (tick & 16) != 0; break;
        case LED_MODE_FAST:      on = (tick & 4)  != 0; break;
        case LED_MODE_ERROR:     on = (tick & 1)  != 0; break;
        default:                 on = false;           break;
    }

    if (on != last_on)
    {
        stm32_gpiowrite(LED_STATUS, on);
        last_on = on;
    }

    tick++;
    return OK;
}
#endif /* CONFIG_NXBOOT_BOOTLOADER */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void led_indicate_init(void)
{
#ifdef CONFIG_NXBOOT_BOOTLOADER
    /* Enable TIM6 clock */
    modifyreg32(STM32_RCC_APB1ENR, 0, RCC_APB1ENR_TIM6EN);

    /* Raise TIM6 priority above default (0x80 → 0x40) */
    putreg32(0x4040, NVIC_IRQ_PRIORITY(STM32_IRQ_TIM6));

    /* Configure TIM6 for periodic interrupt */
    putreg32(0, STM32_TIM6_CNT);
    putreg32(LED_TIM_PSC, STM32_TIM6_PSC);
    putreg32(LED_TIM_ARR, STM32_TIM6_ARR);

    /* Generate update event to load prescaler/reload shadow registers */
    putreg32(BTIM_EGR_UG, STM32_TIM6_EGR);

    /* Clear update flag (set by EGR update generation) */
    putreg32(0, STM32_TIM6_SR);

    /* Enable update interrupt */
    putreg32(ATIM_DIER_UIE, STM32_TIM6_DIER);

    /* Attach ISR and enable NVIC */
    irq_attach(STM32_IRQ_TIM6, led_tim6_isr, NULL);
    up_enable_irq(STM32_IRQ_TIM6);

    /* Start counter */
    putreg32(ATIM_CR1_CEN, STM32_TIM6_CR1);
#endif /* CONFIG_NXBOOT_BOOTLOADER */

}

void led_indicate_uninit(void)
{
#ifdef CONFIG_NXBOOT_BOOTLOADER
    putreg32(0, STM32_TIM6_CR1);        /* Stop counter */
    putreg32(0, STM32_TIM6_DIER);       /* Disable peripheral interrupt */
    putreg32(0, STM32_TIM6_SR);         /* Clear status flags */
    up_disable_irq(STM32_IRQ_TIM6);     /* Disable NVIC line */
    modifyreg32(STM32_RCC_APB1ENR, RCC_APB1ENR_TIM6EN, 0);  /* Disable clock */
    board_autoled_off(1);
#endif
}

void led_indicate_set_mode(int mode)
{
    g_led_mode = mode;
}

/****************************************************************************
 * Name: board_indicate
 *
 * Description:
 *   Weak function override for nxboot progress indication.
 *   Called from nxboot_progress() during bootloader operation.
 *
 ****************************************************************************/

void board_indicate(int msg)
{
    switch (msg)
    {
        case 0:   /* startup_msg */
            g_led_mode = LED_MODE_ON;
            break;

        case 3:   /* found_bootable_image */
        case -1:  /* progress_end */
            g_led_mode = LED_MODE_OFF;
            break;

        case 7:   /* recovery_revert */
        case 9:   /* update_from_update */
            g_led_mode = LED_MODE_FAST;
            break;

        case 10:  /* validate_primary */
        case 11:  /* validate_recovery */
        case 12:  /* validate_update */
            g_led_mode = LED_MODE_SLOW;
            break;

        case 4:   /* no_bootable_image */
        case 5:   /* boardioc_image_boot_fail */
        case 14:  /* recovery_invalid */
        case 15:  /* update_failed */
            g_led_mode = LED_MODE_ERROR;
            break;

        default:
            break;
    }
}

int led_task(int argc, char *argv[])
{
    bool state = false;
    
    while (1) {
        state = !state;
        stm32_gpiowrite(LED_STATUS, state);
        usleep(500000);  // 500ms 翻转，完全独立于系统负载
    }
    return 0;
}


void board_autoled_initialize(void)
{
    /* Configure LED GPIOs for output */
    stm32_configgpio(LED_STATUS);
}

/****************************************************************************
 * Name: board_autoled_on
 ****************************************************************************/

void board_autoled_on(int led)
{

}

/****************************************************************************
 * Name: board_autoled_off
 ****************************************************************************/

void board_autoled_off(int led)
{
    
}