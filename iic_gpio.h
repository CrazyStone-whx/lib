#ifndef IIC_GPIO_H
#define IIC_GPIO_H
//iic-port
#include "stm32f4xx_hal.h"
void iic_gpio_Config(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin, uint32_t Mode,  uint32_t Pull, uint32_t Speed);
#define bI2cScl_Pin GPIO_PIN_8
#define bI2cScl_Port GPIOB

#define bI2cSda_Pin GPIO_PIN_9
#define bI2cSda_Port GPIOB

#define IIC_GPIO_SCL_SET(state)   HAL_GPIO_WritePin(bI2cScl_Port,bI2cScl_Pin,(state)?1:0) 
#define IIC_GPIO_SDA_SET(state)   HAL_GPIO_WritePin(bI2cSda_Port,bI2cSda_Pin,(state)?1:0) 
#define IIC_GPIO_SDA_GET_STATE()  HAL_GPIO_ReadPin(bI2cSda_Port, bI2cSda_Pin))?1:0)
#define IIC_GPIO_SDA_MODE_CON(mode)   iic_gpio_Config (bI2cSda_Port, bI2cSda_Pin, mode?GPIO_MODE_OUTPUT_OD:GPIO_MODE_INPUT, \
 GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH);


//
enum IIC_SDA_MODE
{
 IIC_SDA_INPUT=0,
 IIC_SDA_OUTPUT_OD

};

//iic SCL默认输出模式, sda要在输入输出之间切换
void iic_gpio_init(void);
#define IIC_SCL_H()  IIC_GPIO_SCL_SET(1)
#define IIC_SCL_L()  IIC_GPIO_SCL_SET(0)
#define IIC_SDA_H()  IIC_GPIO_SDA_SET(1)
#define IIC_SDA_L()  IIC_GPIO_SDA_SET(0)
#define IIC_SDA_STATE_GET() IIC_GPIO_SDA_GET_STATE()
#define IIC_SDA_INPUT() IIC_GPIO_SDA_MODE_CON(IIC_SDA_INPUT)
#define IIC_SDA_OUTPUT() IIC_GPIO_SDA_MODE_CON(IIC_SDA_OUTPUT_OD)

#endif