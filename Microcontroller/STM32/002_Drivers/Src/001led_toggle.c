/*
 * 001led_toggle.c
 *
 *  Created on: Jul 2, 2023
 *      Author: moazz
 */



#include "STM32F207ZGxx.h"
#include "STM32F207ZGxx_Gpio_Driver.h"

int main(void)
{
	GPIO_Handle_t GpioLed,GpioSwitch;

	memset(&GpioLed,0,sizeof(GpioLed));
	memset(&GpioSwitch,0,sizeof(GpioSwitch));

	GpioLed.pGPIOx = GPIOB;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OU;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_VERYHIGH;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GpioSwitch.pGPIOx = GPIOB;
	GpioSwitch.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GpioSwitch.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioSwitch.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_VERYHIGH;
	GpioSwitch.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_PP;
	GpioSwitch.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClkCntrl(GPIOB, ENABLE);
	GPIO_Init(&GpioLed);
	GPIO_Init(&GpioSwitch);

	while(1)
	{
		uint8_t value = GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_1);
		if (value)
		{
			for (uint32_t i = 0; i <= 50000; i++);
			GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_7, GPIO_PIN_RESET);
		}
		else
		{
			for (uint32_t i = 0; i <= 50000; i++);
			GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_7, GPIO_PIN_SET);
		}

	}


	return 0;

}
