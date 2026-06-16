/**
*   @file   stm32_myled.c
***********************************************************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif


/***********************************************************************************************************************
*                                                     INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
***********************************************************************************************************************/
#include <nuttx/nuttx.h>
#include <nuttx/irq.h>
#include <nuttx/signal.h>
#include <debug.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include "stm32.h"
#include "mystm32f429igt6.h"
#include <nuttx/myled/myled.h>
#include <arch/board/board.h>
#include <arch/board/board_paths.h>

#include <nuttx/config.h>

#include <stdbool.h>


#ifdef CONFIG_MY_LED
/*add user code*/


/***********************************************************************************************************************
*                                            SOURCE FILE VERSION INFORMATION
***********************************************************************************************************************/
#define STM32_MYLED_SW_MAJOR_VERSION_C             0
#define STM32_MYLED_SW_MINOR_VERSION_C             0
#define STM32_MYLED_SW_PATCH_VERSION_C             0

/***********************************************************************************************************************
*                                                  FILE VERSION CHECKS
***********************************************************************************************************************/
#if ((STM32_MYLED_SW_MAJOR_VERSION_C != STM32_MYLED_SW_MAJOR_VERSION) || \
     (STM32_MYLED_SW_MINOR_VERSION_C != STM32_MYLED_SW_MINOR_VERSION) || \
     (STM32_MYLED_SW_PATCH_VERSION_C != STM32_MYLED_SW_PATCH_VERSION))
#error "Software Version Numbers of stm32_myled.c and stm32_myled.h are different"
#endif


/***********************************************************************************************************************
*                                                   DEFINES AND MACROS
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                                        ENUMS
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                              STATIC VARIABLE DECLARATIONS
***********************************************************************************************************************/


/***********************************************************************************************************************
*                                              GLOBAL VARIABLE DECLARATIONS
***********************************************************************************************************************/

device_file_t g_led_file;

/***********************************************************************************************************************
*                                               STATIC FUNCTION PROTOTYPES
***********************************************************************************************************************/
static bool myled1_read(void);
static void myled1_write(bool ledon);
static bool myled2_read(void);
static void myled2_write(bool ledon);
static bool myled3_read(void);
static void myled3_write(bool ledon);

/***********************************************************************************************************************
*                                              STRUCTURES AND OTHER TYPEDEFS
***********************************************************************************************************************/
struct myled_lower_s myled1_lower = {
    .read = myled1_read,
    .write = myled1_write,
};

struct myled_lower_s myled2_lower = {
    .read = myled2_read,
    .write = myled2_write,
};

struct myled_lower_s myled3_lower = {
    .read = myled3_read,
    .write = myled3_write,
};

/***********************************************************************************************************************
*                                              STATIC FUNCTION DEFINITIONS
***********************************************************************************************************************/
static bool myled1_read(void)
{
    return !stm32_gpioread(BLING_LED_R);
}

static void myled1_write(bool ledon)
{
    stm32_gpiowrite(BLING_LED_R, !ledon);
}

static bool myled2_read(void)
{
    return !stm32_gpioread(BLING_LED_G);
}

static void myled2_write(bool ledon)
{
    stm32_gpiowrite(BLING_LED_G, !ledon);
 }

static bool myled3_read(void)
{
    return !stm32_gpioread(BLING_LED_B);
}

static void myled3_write(bool ledon)
{
    stm32_gpiowrite(BLING_LED_B, !ledon);
}

/***********************************************************************************************************************
*                                              GLOBAL FUNCTION DEFINITIONS
***********************************************************************************************************************/


/****************************************************************************
 * Name: stm32_myled_initialize
 *
 * Description:
 *   Initialize stm32_myled module.
 ****************************************************************************/

static int myled_restore_state(void)
{
    char path[64];
    snprintf(path, sizeof(path), SPI_FLASH_DEVICE_STATUS_DIR "/led_status.bin");
    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return -1;

    uint8_t state;
    lseek(fd, offsetof(device_file_t, led_state), SEEK_SET);
    if (read(fd, &state, sizeof(state)) != sizeof(state))
    {
        close(fd);
        return -1;
    }
    close(fd);

    g_led_file.led_state[0] = state;

    for (int i = 0; i < LED_COUNT; i++)
    {
        bool on = (state >> i) & 1;

        switch (i + 1)
        {
            case 1:  myled1_write(on); break;
            case 2:  myled2_write(on); break;
            case 3:  myled3_write(on); break;
        }
    }

    return 0;
}

int board_myled_initialize(void)
{
    /* configure GPIO pins for LEDs, default to light */
    stm32_configgpio(BLING_LED_R);
    stm32_configgpio(BLING_LED_G);
    stm32_configgpio(BLING_LED_B);

    myled_register("/dev/myled1", &myled1_lower);
    myled_register("/dev/myled2", &myled2_lower);
    myled_register("/dev/myled3", &myled3_lower);

    int ret = myled_restore_state();
    if(ret < 0){
        syslog(LOG_ERR, "restore led state failed\n");    
    }

    syslog(LOG_INFO, "RGB led initialize\n");
    return 0;
}

#endif /* CONFIG_STM32_MYLED */

#ifdef __cplusplus
}
#endif

