/*
 * 005_SPI_Command_Handling.c
 *
 *  Created on: Jul 12, 2023
 *      Author: moazzam
 */

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

#include "STM32F207ZGxx_Gpio_Driver.h"
#include "STM32F207ZGxx_SPI_Driver.h"

//command codes
#define COMMAND_LED_CTRL         50
#define COMMAND_SENSOR_READ      51
#define COMMAND_LED_READ         52
#define COMMAND_PRINT            53
#define COMMAND_ID_READ          54

#define LED_ON                   1
#define LED_OFF                  0

//Arduino Analog pins
#define ANALOG_PIN0              0
#define ANALOG_PIN1              1
#define ANALOG_PIN2              2
#define ANALOG_PIN3              3
#define ANALOG_PIN4              4

//Arduino Led
#define LED_PIN                  9

void spi1_gpio_init(void);
void button_init(void);
void spi1_init(void);
uint8_t SPI_VerifyResponse(uint8_t ackbyte);

GPIO_Handle_t SPI1GpioPins;
GPIO_Handle_t Button;
SPI_Handle_t  SPI1_Handle;


int main()
{
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;

	spi1_gpio_init();
	spi1_init();
	button_init();

	/*
	 * Making SSOE 1 does NSS output enabled
	 * NSS pin is automatically managed by hardware
	 * if SPE = 1 , NSS output will be Low
	 * if SPE = 0 . NSS output will be High
	 */
	SPI_SSOEConfig(SPI1,ENABLE);

	while(1)
	{
		while (!(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)));
		SPI_PeripheralControl(SPI1, ENABLE);

		for (uint32_t i=0 ; i<10000 ; i++); //Delay

		//1.CMD_LED_CTRL	<pin no(1)>		<value(1)>
		uint8_t commandcode = COMMAND_LED_CTRL;
		uint8_t ackbyte;
		uint8_t args[2];

		//send command
		SPI_SendData(SPI1, &commandcode, 1);
		//do dummy read to clear off RXNIE flag
		SPI_ReceiveData(SPI1, &dummy_read, 1);

		//send some dummy bits to fetch the response from the slave
		SPI_SendData(SPI1, &dummy_write, 1);
		//Read the ack byte received
		SPI_ReceiveData(SPI1, &ackbyte, 1);

		if (SPI_VerifyResponse(ackbyte))
		{
			args[0] = LED_PIN;
			args[1] = LED_ON;

			//send arguments
			SPI_SendData(SPI1, args, 2);
			//do dummy read to clear off RXNIE flag
			SPI_ReceiveData(SPI1, &dummy_read, 1);
		}


		//lets confirm SPI peripheral is not busy
		while (SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

		SPI_PeripheralControl(SPI1, DISABLE);
	}

	while(1);
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

uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
	if (ackbyte == 0xF5)
	{
		//ack
		return 1;
	}
	return 0;
}
