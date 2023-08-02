/*
 * 003_spi_tx_test.c
 *
 *  Created on: Jul 2, 2023
 *      Author: moazzam
 *
 */


#include "STM32F207ZGxx_Gpio_Driver.h"
#include "STM32F207ZGxx_SPI_Driver.h"

/*
 * SPI pins
 * PA4   SPI1_NSS
 * PA5   SPI1_SCK
 * PA6   SPI1_MISO
 * PA7   SPI1_MOSI
 */

void SPI1_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

	memset(&SPIPins , 0 ,sizeof(SPIPins));

	SPIPins.pGPIOx = GPIOA;

	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_VERYHIGH;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&SPIPins);

	//SCK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPIPins);


}

void SPI1_Inits(void)
{
	SPI_Handle_t SPI1_Handle;

	memset(&SPI1_Handle , 0 ,sizeof(SPI1_Handle));

	SPI1_Handle.pSPIx = SPI1;

	SPI1_Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI1_Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
	SPI1_Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI1_Handle.SPIConfig.SPI_SSM = SPI_SSM_EN;
	SPI1_Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI1_Handle.SPIConfig.SPI_CPOL = SPI_CPOL_IDLE_LOW;

	SPI_Init(&SPI1_Handle);
}

int main ()
{
	uint8_t user_data[] = "Hello World";

	SPI1_GPIOInits();
	SPI1_Inits();

	//This makes nss signal internally high and avoid ModeF
	SPI_SSIConfig(SPI1 , ENABLE);

	SPI_PeripheralControl(SPI1 , ENABLE);

	SPI_SendData(SPI1, (uint8_t *)user_data, strlen((char *)user_data));

	while(1);

	return 0;

}
