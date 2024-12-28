#include <nuttx/nuttx.h>
#include <nuttx/irq.h>
#include <nuttx/signal.h>
#include <debug.h>
#include <assert.h>
#include <errno.h>
#include "stm32.h"
#include "stm32f429i-disco.h"
// #include <nuttx/simulative_i2c/simulative_i2c.h>
#include <arch/board/board.h>


#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/i2c/i2c_master.h>
// #include <nuttx/input/gt9xx.h>

// #include "stm32_i2c.h"
#include "/home/zeki/workspace/NuttX/nuttxspace/nuttx/arch/arm/src/stm32/stm32_i2c.c"


#ifdef CONFIG_MY_TOUCH

// /****************************************************************************
//  * Private Data
//  ****************************************************************************/
// static int my_gt9xx_irq_attach(const struct gt9xx_board_s *state,xcpt_t isr, void *arg);
// static void my_gt9xx_irq_enable(const struct gt9xx_board_s *state,bool enable);
// static int my_gt9xx_set_power(const struct gt9xx_board_s *state,bool on);

// /* Callback for Board-Specific Operations */

// static const struct gt9xx_board_s g_pinephone_gt9xx =
// {
//   .irq_attach = my_gt9xx_irq_attach,
//   .irq_enable = my_gt9xx_irq_enable,
//   .set_power  = my_gt9xx_set_power
// };

// /****************************************************************************
//  * Private Functions
//  ****************************************************************************/

// /****************************************************************************
//  * Name: pinephone_gt9xx_irq_attach
//  *
//  * Description:
//  *   Attach the Interrupt Handler for Touch Panel.
//  *
//  * Input Parameters:
//  *   state - Callback for Board-Specific Operations
//  *   isr   - Interrupt Handler
//  *   arg   - Argument for Interrupt Handler
//  *
//  * Returned Value:
//  *   Zero (OK) on success; a negated errno value is returned on any failure.
//  *
//  ****************************************************************************/

// static int my_gt9xx_irq_attach(const struct gt9xx_board_s *state,
//                                       xcpt_t isr, void *arg)
// {
//   // int ret;

//   // iinfo("\n");
//   // DEBUGASSERT(state != NULL && isr != NULL && arg != NULL);

//   // /* Attach the Interrupt Handler to Port PH */

//   // ret = irq_attach(A64_IRQ_PH_EINT, isr, arg);
//   // if (ret < 0)
//   //   {
//   //     ierr("Attach Interrupt Handler failed: %d\n", ret);
//   //     return ret;
//   //   }

//   // /* Set Interrupt Priority in Generic Interrupt Controller v2 */

//   // arm64_gic_irq_set_priority(A64_IRQ_PH_EINT, 0, IRQ_TYPE_EDGE);

//   // /* Enable Interrupts for Port PH */

//   // up_enable_irq(A64_IRQ_PH_EINT);

//   return OK;
// }

// /****************************************************************************
//  * Name: pinephone_gt9xx_irq_enable
//  *
//  * Description:
//  *   Enable or disable Interrupts for the Touch Panel.
//  *
//  * Input Parameters:
//  *   state  - Callback for Board-Specific Operations
//  *   enable - True to enable interrupts; False to disable interrupts
//  *
//  * Returned Value:
//  *   Zero (OK) on success; a negated errno value is returned on any failure.
//  *
//  ****************************************************************************/

// static void my_gt9xx_irq_enable(const struct gt9xx_board_s *state,
//                                        bool enable)
// {
//   // int ret;

//   // iinfo("enable=%d\n", enable);
//   // DEBUGASSERT(state != NULL);

//   // if (enable)
//   //   {
//   //     /* Configure the Touch Panel Interrupt */

//   //     ret = a64_pio_config(CTP_INT);
//   //     if (ret < 0)
//   //       {
//   //         ierr("Configure Touch Panel Interrupt failed: %d\n", ret);
//   //         return;
//   //       }

//   //     /* Enable the Touch Panel Interrupt */

//   //     ret = a64_pio_irqenable(CTP_INT);
//   //     if (ret < 0)
//   //       {
//   //         ierr("Enable Touch Panel Interrupt failed: %d\n", ret);
//   //         return;
//   //       }
//   //   }
//   // else
//   //   {
//   //     /* Disable the Touch Panel Interrupt */

//   //     ret = a64_pio_irqdisable(CTP_INT);
//   //     if (ret < 0)
//   //       {
//   //         ierr("Disable Touch Panel Interrupt failed: %d\n", ret);
//   //         return;
//   //       }
//   //   }
// }

// /****************************************************************************
//  * Name: pinephone_gt9xx_set_power
//  *
//  * Description:
//  *   Power on or off the Touch Panel.
//  *
//  * Input Parameters:
//  *   state - Callback for Board-Specific Operations
//  *   on    - True to power on; False to power off
//  *
//  * Returned Value:
//  *   Zero (OK) on success; a negated errno value is returned on any failure.
//  *
//  ****************************************************************************/

// static int my_gt9xx_set_power(const struct gt9xx_board_s *state,
//                                      bool on)
// {
//   /* Assume that Touch Panel is already powered on by pinephone_pmic_init() */

// //   iinfo("on=%d\n", on);
// //   return OK;
// }

void board_touch_initialize(void)
{
//     int ret;
    struct i2c_master_s *i2c = NULL;
    //const char devpath = "/dev/mytouch";
    stm32_configgpio(GPIO_TOUCH_RST);

    stm32_configgpio(GPIO_TOUCH_INT1); //TODO:配置触控芯片没有生效？
    

    //DELAY
    sleep(1); //TODO:
    stm32_gpiowrite(GPIO_TOUCH_INT1, 1);
    //DELAY
    sleep(1); //TODO:
    stm32_configgpio(GPIO_TOUCH_INT2);


//     DEBUGASSERT(devpath != NULL && i2c != NULL);
    //gt9xx_register(devpath, i2c, 0xBA, &g_pinephone_gt9xx);
}

void stm32_i2c_register(int bus)
{
  struct i2c_master_s *i2c;
  int ret;
  syslog(LOG_DEBUG,"in stm32_i2c_register\n");
  i2c = stm32_i2cbus_initialize(2);
  if (i2c == NULL)
    {
      syslog(LOG_DEBUG,"in stm32_i2c_register 198\n");
      _err("ERROR: Failed to get I2C%d interface\n", bus);
    }
  else
    {
      ret = i2c_register(i2c, bus);
      if (ret < 0)
        {
          syslog(LOG_DEBUG,"in stm32_i2c_register 206\n");
          _err("ERROR: Failed to register I2C%d driver: %d\n", bus, ret);
          stm32_i2cbus_uninitialize(i2c);
        }
    }
}

#endif
