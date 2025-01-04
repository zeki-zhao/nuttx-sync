#include <nuttx/nuttx.h>
#include <nuttx/irq.h>
#include <nuttx/signal.h>
#include <debug.h>
#include <assert.h>
#include <errno.h>
#include "stm32.h"
#include "mystm32f429igt6.h"
// #include <nuttx/simulative_i2c/simulative_i2c.h>
#include <arch/board/board.h>


#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/i2c/i2c_master.h>
#include <nuttx/input/gt9xx.h>

// #include "stm32_i2c.h"
// #include "/home/zeki/workspace/NuttX/nuttxspace/nuttx/arch/arm/src/stm32/stm32_i2c_v2.c"

#ifdef CONFIG_MY_TOUCH

#define TOUCH_ADDR 0x5d
// /****************************************************************************
//  * Private Data
//  ****************************************************************************/
static int my_gt9xx_irq_attach(const struct gt9xx_board_s *state,xcpt_t isr, void *arg);
static void my_gt9xx_irq_enable(const struct gt9xx_board_s *state,bool enable);
static int my_gt9xx_set_power(const struct gt9xx_board_s *state,bool on);

// /* Callback for Board-Specific Operations */

static const struct gt9xx_board_s my_gt9xx =
{
  .irq_attach = my_gt9xx_irq_attach,
  .irq_enable = my_gt9xx_irq_enable,
  .set_power  = my_gt9xx_set_power
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: pinephone_gt9xx_irq_attach
 *
 * Description:
 *   Attach the Interrupt Handler for Touch Panel.
 *
 * Input Parameters:
 *   state - Callback for Board-Specific Operations
 *   isr   - Interrupt Handler
 *   arg   - Argument for Interrupt Handler
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value is returned on any failure.
 *
//  ****************************************************************************/

static xcpt_t g_isr;
static void *g_arg;
static int my_gt9xx_irq_attach(const struct gt9xx_board_s *state,xcpt_t isr, void *arg)
{
  // int ret;

  // iinfo("\n");
  // DEBUGASSERT(state != NULL && isr != NULL && arg != NULL);

  // /* Attach the Interrupt Handler to Port PH */

  // ret = irq_attach(A64_IRQ_PH_EINT, isr, arg);
  // if (ret < 0)
  //   {
  //     ierr("Attach Interrupt Handler failed: %d\n", ret);
  //     return ret;
  //   }

  // /* Set Interrupt Priority in Generic Interrupt Controller v2 */

  // arm64_gic_irq_set_priority(A64_IRQ_PH_EINT, 0, IRQ_TYPE_EDGE);

  // /* Enable Interrupts for Port PH */

  // up_enable_irq(A64_IRQ_PH_EINT);
  // return OK;
    
  wlinfo("Attach IRQ\n");
  g_isr = isr;
  g_arg = arg;
  stm32_gpiosetevent(GPIO_TOUCH_INT2, false, true, false, g_isr, g_arg); //TODO:在形参出设置了触发方式
  return OK;
}

/****************************************************************************
 * Name: pinephone_gt9xx_irq_enable
 *
 * Description:
 *   Enable or disable Interrupts for the Touch Panel.
 *
 * Input Parameters:
 *   state  - Callback for Board-Specific Operations
 *   enable - True to enable interrupts; False to disable interrupts
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value is returned on any failure.
 *
 ****************************************************************************/

static void my_gt9xx_irq_enable(const struct gt9xx_board_s *state,
                                       bool enable)
{
  // int ret;

  // iinfo("enable=%d\n", enable);
  // DEBUGASSERT(state != NULL);

  // if (enable)
  //   {
  //     /* Configure the Touch Panel Interrupt */

  //     ret = a64_pio_config(CTP_INT);
  //     if (ret < 0)
  //       {
  //         ierr("Configure Touch Panel Interrupt failed: %d\n", ret);
  //         return;
  //       }

  //     /* Enable the Touch Panel Interrupt */

  //     ret = a64_pio_irqenable(CTP_INT);
  //     if (ret < 0)
  //       {
  //         ierr("Enable Touch Panel Interrupt failed: %d\n", ret);
  //         return;
  //       }
  //   }
  // else
  //   {
  //     /* Disable the Touch Panel Interrupt */

  //     ret = a64_pio_irqdisable(CTP_INT);
  //     if (ret < 0)
  //       {
  //         ierr("Disable Touch Panel Interrupt failed: %d\n", ret);
  //         return;
  //       }
  //   }
  // struct gt9xx_board_s *priv = (struct gt9xx_board_s *)state;
    irqstate_t flags;

    /* Attach and enable, or detach and disable.  Enabling and disabling GPIO
    * interrupts is a multi-step process so the safest thing is to keep
    * interrupts disabled during the reconfiguration.
    */

    flags = enter_critical_section();
    if (enable)
    {
        /* Configure the EXTI interrupt using the SAVED handler */

        stm32_gpiosetevent(GPIO_TOUCH_INT2, false, true, false, g_isr, g_arg);
    }
    else
    {
        /* Configure the EXTI interrupt with a NULL handler to disable it */

        stm32_gpiosetevent(GPIO_TOUCH_INT2, false, false, false,NULL, NULL);
    }

    leave_critical_section(flags);
}

/****************************************************************************
 * Name: pinephone_gt9xx_set_power
 *
 * Description:
 *   Power on or off the Touch Panel.
 *
 * Input Parameters:
 *   state - Callback for Board-Specific Operations
 *   on    - True to power on; False to power off
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value is returned on any failure.
 *
 ****************************************************************************/

static int my_gt9xx_set_power(const struct gt9xx_board_s *state,
                                     bool on)
{
  /* Assume that Touch Panel is already powered on by pinephone_pmic_init() */

  iinfo("on=%d\n", on);
  return OK;
}
/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: myled_ioctl
 ****************************************************************************/

void board_touch_initialize(void)
{

    struct i2c_master_s *i2c;
    const char devpath[] = "/dev/mytouch";
    int ret;
    syslog(LOG_DEBUG,"in stm32_i2c_register\n");
    i2c = stm32_i2cbus_initialize(2);
    if (i2c == NULL)
    {
        syslog(LOG_DEBUG,"in stm32_i2c_register 198\n");
        _err("ERROR: Failed to get I2C%d interface\n", 2);
    }
    else
    {
        ret = i2c_register(i2c, 2);
        if (ret < 0)
        {
            syslog(LOG_DEBUG,"in stm32_i2c_register 206\n");
            _err("ERROR: Failed to register I2C%d driver: %d\n", 2, ret);
            stm32_i2cbus_uninitialize(i2c);
        }
    }
//     int ret;
    syslog(LOG_DEBUG,"in %s:%d\n",__func__,__LINE__);

    stm32_configgpio(GPIO_TOUCH_RST);
    stm32_configgpio(GPIO_TOUCH_INT1); //TODO:配置触控芯片没有生效？
    //DELAY
    sleep(1); //TODO:大于100us
    stm32_gpiowrite(GPIO_TOUCH_RST, 1);
    //DELAY
    sleep(1); //TODO:大于5ms
    stm32_configgpio(GPIO_TOUCH_INT2);
    // syslog(LOG_DEBUG,"in %s:%d\n",__func__,__LINE__);

    DEBUGASSERT(devpath != NULL && i2c != NULL);
    gt9xx_register(devpath, i2c, TOUCH_ADDR, &my_gt9xx);
    // register_driver("/dev/mytouch", &g_gt9xx_fileops, 0666, &test);

    // syslog(LOG_DEBUG,"in %s:%d\n",__func__,__LINE__);
}

void stm32_i2c_register(int bus)
{
    // struct i2c_master_s *i2c;
    // int ret;
    // syslog(LOG_DEBUG,"in stm32_i2c_register\n");
    // i2c = stm32_i2cbus_initialize(2);
    // if (i2c == NULL)
    // {
    //     syslog(LOG_DEBUG,"in stm32_i2c_register 198\n");
    //     _err("ERROR: Failed to get I2C%d interface\n", bus);
    // }
    // else
    // {
    //     ret = i2c_register(i2c, bus);
    //     if (ret < 0)
    //     {
    //         syslog(LOG_DEBUG,"in stm32_i2c_register 206\n");
    //         _err("ERROR: Failed to register I2C%d driver: %d\n", bus, ret);
    //         stm32_i2cbus_uninitialize(i2c);
    //     }
    // }
}

#endif
