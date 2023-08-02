/*
 * 004_SPI_Arduino_test.c
 *
 *  Created on: Jul 7, 2023
 *      Author: moazzam
 */

#include "STM32F207ZGxx_Gpio_Driver.h"
#include "STM32F207ZGxx_SPI_Driver.h"

void spi1_gpio_init(void);
void button_init(void);
void spi1_init(void);

/*
 * SPI1 pins
 * PA4   SPI1_NSS
 * PA5   SPI1_SCK
 * PA6   SPI1_MISO
 * PA7   SPI1_MOSI
 */

/*
 * PC13  Button
 */

GPIO_Handle_t SPI1GpioPins;
GPIO_Handle_t Button;
SPI_Handle_t  SPI1_Handle;

int main ()
{
	spi1_gpio_init();
	button_init();
	spi1_init();

	/*
	 * Making SSOE 1 does NSS output enabled
	 * NSS pin is automatically managed by hardware
	 * if SPE = 1 , NSS output will be Low
	 * if SPE = 0 . NSS output will be High
	 */
	SPI_SSOEConfig(SPI1,ENABLE);

	char msg[10] = "Hello";

	while(1)
	{
		while (!(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)));
		SPI_PeripheralControl(SPI1, ENABLE);
		for (uint32_t i=0 ; i<50000 ; i++);
		SPI_SendData(SPI1, (uint8_t *)msg, strlen((char *)msg));

		//lets confirm SPI peripheral is not busy
		while (SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

		SPI_PeripheralControl(SPI1, DISABLE);
	}

	return 1;

}

void spi1_gpio_init(void)
{
	SPI1GpioPins.pGPIOx = GPIOA;

	SPI1GpioPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_PP;
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//SPI1_NSS
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinNumber = 4;
	GPIO_Init(&SPI1GpioPins);

	//SPI1_SCK
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_Init(&SPI1GpioPins);

	//SPI1_MSIO
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinNumber = 6;
	GPIO_Init(&SPI1GpioPins);

	//SPI1_MOSI
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinNumber = 7;
	GPIO_Init(&SPI1GpioPins);

}

void spi1_init(void)
{
	SPI1_Handle.pSPIx = SPI1;

	SPI1_Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI1_Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI1_Handle.SPIConfig.SPI_CPOL = SPI_CPOL_IDLE_LOW;
	SPI1_Handle.SPIConfig.SPI_DFF = SPI_DFF_8BIT;
	SPI1_Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI1_Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;
	SPI1_Handle.SPIConfig.SPI_SSM = SPI_SSM_DI;

	SPI_Init(&SPI1_Handle);

}

void button_init()
{
	SPI1GpioPins.pGPIOx = GPIOC;

	SPI1GpioPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_PP;
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//SPI1_NSS
	SPI1GpioPins.GPIO_PinConfig.GPIO_PinNumber = 13;
	GPIO_Init(&SPI1GpioPins);
}

