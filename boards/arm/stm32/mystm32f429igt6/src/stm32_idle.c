/****************************************************************************
 * boards/arm/stm32/stm32f429i-disco/src/stm32_idle.c
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

#include <arch/board/board.h>
#include <nuttx/config.h>

#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/board.h>
#include <nuttx/clock.h>
#include <nuttx/power/pm.h>

#include <nuttx/irq.h>

#include "arm_internal.h"
#include "stm32_pm.h"
#include "stm32_rcc.h"
#include "stm32_exti.h"

#include "mystm32f429igt6.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

/* Does the board support an IDLE LED to indicate that the board is in the
 * IDLE state?
 */

#if defined(CONFIG_ARCH_LEDS) && defined(LED_IDLE)
#  define BEGIN_IDLE() board_autoled_on(LED_IDLE)
#  define END_IDLE()   board_autoled_off(LED_IDLE)
#else
#  define BEGIN_IDLE()
#  define END_IDLE()
#endif

/* Values for the RTC Alarm to wake up from the PM_STANDBY mode */

#ifndef CONFIG_PM_ALARM_SEC
#  define CONFIG_PM_ALARM_SEC 3
#endif

#ifndef CONFIG_PM_ALARM_NSEC
#  define CONFIG_PM_ALARM_NSEC 0
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

#if defined(CONFIG_PM) && defined(CONFIG_RTC_ALARM)
static void stm32_alarmcb(void);
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_alarmcb
 *
 * Description:
 *    RTC alarm service routine
 *
 ****************************************************************************/

#if defined(CONFIG_PM) && defined(CONFIG_RTC_ALARM)
static void stm32_alarmcb(void)
{
  /* This alarm occurs because there wasn't any EXTI interrupt during the
   * PM_STANDBY period. So just go to sleep.
   */

  pm_changestate(PM_IDLE_DOMAIN, PM_SLEEP);
}
#endif
