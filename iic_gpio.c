#include "iic_gpio.h"
void iic_gpio_Config(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin, uint32_t Mode,  uint32_t Pull, uint32_t Speed)
{
    GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin = GPIO_Pin;
  GPIO_InitStruct.Mode = Mode;
  GPIO_InitStruct.Pull = Pull;
  GPIO_InitStruct.Speed = Speed;
  HAL_GPIO_Init (GPIOx, &GPIO_InitStruct);

}

void iic_gpio_init(void)
{
    iic_gpio_Config (bI2cSda_Port, bI2cSda_Pin, GPIO_MODE_OUTPUT_PP,
            GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH);
    iic_gpio_Config (bI2cScl_Port, bI2cScl_Pin, GPIO_MODE_OUTPUT_PP,
            GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH);
    IIC_GPIO_SCL_SET(1);
    IIC_GPIO_SDA_SET(1);
}


