/*
 * 002_Gpio_interrupt.c
 *
 *  Created on: Jul 3, 2023
 *      Author: moazzam
 */


#include "STM32F207ZGxx_Gpio_Driver.h"


int main(void)
{
	GPIO_Handle_t GpioLed,GpioSwitch;

	memset(&GpioLed,0,sizeof(GpioLed));
	memset(&GpioSwitch,0,sizeof(GpioSwitch));

	GPIO_PeriClkCntrl(GPIOB, ENABLE);

	GpioLed.pGPIOx = GPIOB;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OU;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_VERYHIGH;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GpioLed);

	GpioSwitch.pGPIOx = GPIOB;
	GpioSwitch.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GpioSwitch.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioSwitch.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_VERYHIGH;
	GpioSwitch.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIO_Init(&GpioSwitch);

	//IRQ configuration
	GPIO_PriorityConfig(IRQ_NO_EXTI1, 15);
	GPIO_InterruptConfig(IRQ_NO_EXTI1, ENABLE);

	while(1)
	{

	}


	return 0;

}

void EXTI1_IRQHandler(void)
{
	for (uint32_t i=0 ; i<50000 ; i++);
	GPIO_IRQHandling(GPIO_PIN_NO_1);

	GPIO_ToggleOutputPin(GPIOB, GPIO_PIN_NO_7);
}
