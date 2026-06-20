/****************************************************************************
 * boards/arm/stm32/mystm32f429igt6/src/stm32_buzzer.c
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <arch/board/board.h>
#include <nuttx/irq.h>
#include "stm32_tim.h"
#include "stm32.h"
#include "mystm32f429igt6.h"

/* Note name → half_period_us lookup (C3–B7 at 1 MHz timer clock) */
static const struct {
    const char *name;
    uint16_t    hp;
} g_note_table[] =
{
    {"R",     0}, 
    {"C3", 3821}, {"C#3",3607}, {"D3", 3404}, {"D#3",3213},
    {"E3", 3033}, {"F3", 2862}, {"F#3",2702}, {"G3", 2550},
    {"G#3",2407}, {"A3", 2272}, {"A#3",2144}, {"B3", 2024},
    {"C4", 1910}, {"C#4",1803}, {"D4", 1702}, {"D#4",1606},
    {"E4", 1516}, {"F4", 1431}, {"F#4",1350}, {"G4", 1275},
    {"G#4",1203}, {"A4", 1135}, {"A#4",1072}, {"B4", 1011},
    {"C5",  955}, {"C#5", 901}, {"D5",  850}, {"D#5", 803},
    {"E5",  757}, {"F5",  715}, {"F#5", 675}, {"G5",  637},
    {"G#5", 601}, {"A5",  567}, {"A#5", 535}, {"B5",  505},
    {"C6",  477}, {"C#6", 450}, {"D6",  425}, {"D#6", 401},
    {"E6",  378}, {"F6",  357}, {"F#6", 337}, {"G6",  318},
    {"G#6", 300}, {"A6",  283}, {"A#6", 267}, {"B6",  252},
    {"C7",  238}, {"C#7", 224}, {"D7",  212}, {"D#7", 200},
    {"E7",  189}, {"F7",  178}, {"F#7", 168}, {"G7",  158},
    {"G#7", 149}, {"A7",  141}, {"A#7", 133}, {"B7",  126},
};

int board_note_to_hp(const char *name)
{
    for (size_t i = 0; i < sizeof(g_note_table)/sizeof(g_note_table[0]); i++)
    {
        if (strcasecmp(name, g_note_table[i].name) == 0)
            return g_note_table[i].hp;
    }
    return -1;
}

static struct stm32_tim_dev_s *g_tim_dev = NULL;
static volatile bool           g_buzzer_state = false;

static int buzzer_isr(int irq, void *context, void *arg)
{
    STM32_TIM_ACKINT(g_tim_dev, GTIM_SR_UIF);

    g_buzzer_state = !g_buzzer_state;
    stm32_gpiowrite(GPIO_BEEP, g_buzzer_state);

    return OK;
}

void board_buzzer_init(void)
{
    stm32_configgpio(GPIO_BEEP);

    g_tim_dev = stm32_tim_init(3);
    if (g_tim_dev == NULL)
        printf("buzzer: stm32_tim_init(3) failed\n");
}

void board_buzzer_start(int half_period_us)
{
    if (g_tim_dev == NULL)
        return;

    STM32_TIM_SETCLOCK(g_tim_dev, 1000000);
    STM32_TIM_DISABLE(g_tim_dev);
    STM32_TIM_SETMODE(g_tim_dev, STM32_TIM_MODE_UP);
    STM32_TIM_SETPERIOD(g_tim_dev, half_period_us);
    STM32_TIM_ACKINT(g_tim_dev, GTIM_SR_UIF);
    STM32_TIM_SETISR(g_tim_dev, buzzer_isr, NULL, 0);
    STM32_TIM_ENABLEINT(g_tim_dev, GTIM_DIER_UIE);
    g_buzzer_state = false;
    STM32_TIM_ENABLE(g_tim_dev);
}

void board_buzzer_stop(void)
{
    if (g_tim_dev == NULL)
        return;

    STM32_TIM_DISABLE(g_tim_dev);
    STM32_TIM_DISABLEINT(g_tim_dev, GTIM_DIER_UIE);
    STM32_TIM_SETISR(g_tim_dev, NULL, NULL, 0);

    g_buzzer_state = false;
    stm32_gpiowrite(GPIO_BEEP, false);
}

void board_buzzer_set_period(int half_period_us)
{
    if (g_tim_dev == NULL)
        return;

    STM32_TIM_SETPERIOD(g_tim_dev, half_period_us);
    STM32_TIM_SETCOUNTER(g_tim_dev, 0);
    STM32_TIM_ACKINT(g_tim_dev, GTIM_SR_UIF);
}
