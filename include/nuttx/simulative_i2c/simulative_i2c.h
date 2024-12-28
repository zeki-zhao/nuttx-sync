#ifndef __DRIVERS_SIMULATIVE_I2C_H__
#define __DRIVERS_SIMULATIVE_I2C_H__

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <nuttx/fs/ioctl.h>

#include "stm32.h"
// #include "stm32f429i-disco.h"
#include <arch/board/board.h>


//软件IIC使用的宏
#define I2C_SCL_1()  stm32_gpiowrite(GPIO_I2C_SCL,1)		/* SCL = 1 */
#define I2C_SCL_0()  stm32_gpiowrite(GPIO_I2C_SCL,0)		/* SCL = 0 */

#define I2C_SDA_1()  stm32_gpiowrite(GPIO_I2C_SDA,1)		/* SDA = 1 */
#define I2C_SDA_0()  stm32_gpiowrite(GPIO_I2C_SDA,0)		/* SDA = 0 */

#define I2C_SDA_READ()  stm32_gpioread(GPIO_I2C_SDA)	/* 读SDA口线状态 */

void stm32_i2c_register(int bus);


#endif