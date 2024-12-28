#include <nuttx/nuttx.h>
#include <nuttx/irq.h>
#include <nuttx/signal.h>
#include <debug.h>
#include <assert.h>
#include <errno.h>
#include "stm32.h"
#include "stm32f429i-disco.h"
#include <nuttx/myled/myled.h>
#include <arch/board/board.h>



#ifdef CONFIG_MY_LED

static bool get_myled_state(int lednum);
static void set_myled_param(int lednum, bool ledon);


struct myled_lower_s myled_lower = {
    .getio = get_myled_state,
    .setio = set_myled_param,
    .ioctl = set_myled_param,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/
static bool get_myled_state(int lednum)
{
    switch(lednum)
    {
    case 1:
        {
            return stm32_gpioread(BLING_LED_R);
        }
    break;
    case 2:
        {
            return stm32_gpioread(BLING_LED_G);
        }
    break;
    case 3:
        {
            return stm32_gpioread(BLING_LED_B);
        }
    break;
    default:
    break;
    }
}

static void set_myled_param(int lednum, bool ledon)
{
    switch(lednum)
    {
    case 1:
        {
            stm32_gpiowrite(BLING_LED_R, ledon);
        }
    break;
    case 2:
        {
            stm32_gpiowrite(BLING_LED_G, ledon);
        }
    break;
    case 3:
        {
            stm32_gpiowrite(BLING_LED_B, ledon);
        }
    break;
    default:
    break;
    }
}


void board_myled_initialize(void)
{
    stm32_configgpio(BLING_LED_R);
    stm32_configgpio(BLING_LED_G);
    stm32_configgpio(BLING_LED_B);

     
     myled_register("/dev/myled" , &myled_lower);
}

#endif
