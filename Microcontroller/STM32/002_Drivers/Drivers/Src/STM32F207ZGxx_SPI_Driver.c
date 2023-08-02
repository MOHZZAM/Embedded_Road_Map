/*
 * STM32F207ZGxx_SPI_Driver.c
 *
 *  Created on: Jul 2, 2023
 *      Author: moazzam
 */

#include "STM32F207ZGxx_SPI_Driver.h"


/***************************************************
 * @fun                - SPI_PeriClkCntrl
 *
 * @brief              - This function Enables or Disables peripheral clock of particular SPI
 *
 * @param[in]          - Base address of SPI Peripheral
 * @param[in]          - ENABLE or DISABLE
 *
 * @return             - none
 *
 * @note               - none
 */
void SPI_PeriClkCntrl(SPI_RegDef_t *pSPIx , uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if (pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if (pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}


	}

	else
	{
		if (pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}
		else if (pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}
		else if (pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
	}
}


/***************************************************
 * @fun                - SPI_Init
 *
 * @brief              - This function initializes particular SPI
 *
 * @param[in]          - Base address of SPI Handle
 *
 * @return             - none
 *
 * @note               - none
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	//Peripheral clock enable
	SPI_PeriClkCntrl(pSPIHandle->pSPIx, ENABLE);

	// 1. SPI device mode
	pSPIHandle->pSPIx->CR1 &= ~( pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR);
	pSPIHandle->pSPIx->CR1 |= ( pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR);

	//2. SPI bus configuration
	if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		pSPIHandle->pSPIx->CR1 &= ~( 1 << SPI_CR1_BIDI);
	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		pSPIHandle->pSPIx->CR1 |= ( 1 << SPI_CR1_BIDI);
	}
	else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		pSPIHandle->pSPIx->CR1 &= ~( 1 << SPI_CR1_BIDI);
		pSPIHandle->pSPIx->CR1 |= ( 1 << SPI_CR1_RX_ONLY);
	}

	//3. SPI serial clock speed
	pSPIHandle->pSPIx->CR1 &= ~( pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR);
	pSPIHandle->pSPIx->CR1 |= ( pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR);

	//4. SPI data frame format
	pSPIHandle->pSPIx->CR1 &= ~( pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF);
	pSPIHandle->pSPIx->CR1 |= ( pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF);

	//5. SPI clock phase
	pSPIHandle->pSPIx->CR1 &= ~( pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA);
	pSPIHandle->pSPIx->CR1 |= ( pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA);

	//6. SPI clock polarity
	pSPIHandle->pSPIx->CR1 &= ~( pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL);
	pSPIHandle->pSPIx->CR1 |= ( pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL);

	//6. SPI software slave select
	pSPIHandle->pSPIx->CR1 &= ~( pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM);
	pSPIHandle->pSPIx->CR1 |= ( pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM);

}


/***************************************************
 * @fun                - SPI_DeInit
 *
 * @brief              - This function de-initializes particular SPI
 *
 * @param[in]          - Base address of SPI peripheral
 *
 * @return             - none
 *
 * @note               - none
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if (pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}
	else if (pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}
	else if (pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	}
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName)
{
	if (pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/***************************************************
 * @fun                - SPI_SendData
 *
 * @brief              - This function Send data using particular SPI
 *
 * @param[in]          - Base address of SPI peripheral
 * @param[in]          - Base address of Transmit buffer of SPI
 * @param[in]          - Length of data
 *
 * @return             - none
 *
 * @note               - This is blocking call
 */
void SPI_SendData(SPI_RegDef_t *pSPIx , uint8_t *pTxBuffer , uint32_t Len)
{
	while (Len > 0)
	{
		//1. wait until TXE buffer gets empty
		while(SPI_GetFlagStatus(pSPIx , SPI_TXE_FLAG) == FLAG_RESET);

		//2.Check DFF bit in CR1
		if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			//16 bit
			pSPIx->DR = *(uint16_t *)(pTxBuffer);
			Len--;
			Len--;
			(uint16_t *)(pTxBuffer)++;
		}
		else
		{
			//8 bit
			pSPIx->DR = *(pTxBuffer);
			Len--;
			pTxBuffer++;
		}
	}

}


/***************************************************
 * @fun                - SPI_ReceiveData
 *
 * @brief              - This function Receive data on particular SPI
 *
 * @param[in]          - Base address of SPI peripheral
 * @param[in]          - Base address of Receive buffer of SPI
 * @param[in]          - Length of data
 *
 * @return             - none
 *
 * @note               - none
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx , uint8_t *pRxBuffer , uint32_t Len)
{
	while (Len > 0)
	{
		//1. wait until TXE buffer gets empty
		while(SPI_GetFlagStatus(pSPIx , SPI_RXNE_FLAG) == FLAG_RESET);

		//2.Check DFF bit in CR1
		if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			//16 bit
			*(uint16_t *)(pRxBuffer) = pSPIx->DR;
			Len--;
			Len--;
			(uint16_t *)(pRxBuffer)++;
		}
		else
		{
			//8 bit
			*(pRxBuffer) = pSPIx->DR;
			Len--;
			pRxBuffer++;
		}
	}
}


/***************************************************
 * @fun                - SPI_PeripheralControl
 *
 * @brief              - This function Enable SPI
 *
 * @param[in]          - Base address of SPI peripheral
 * @param[in]          - ENABLE or DISABLE
 *
 * @return             - none
 *
 * @note               - none
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx , uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}


/***************************************************
 * @fun                - SPI_SSIConfig
 *
 * @brief              - This function Enable SPI
 *
 * @param[in]          - Base address of SPI peripheral
 * @param[in]          - ENABLE or DISABLE
 *
 * @return             - none
 *
 * @note               - none
 */
void SPI_SSIConfig(SPI_RegDef_t *pSPIx , uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}


/***************************************************
 * @fun                - SPI_SSOEConfig
 *
 * @brief              - This function Enable SPI
 *
 * @param[in]          - Base address of SPI peripheral
 * @param[in]          - ENABLE or DISABLE
 *
 * @return             - none
 *
 * @note               - none
 */
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx , uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}
	else
	{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}

/***************************************************
 * @fun                - SPI_InterruptConfig
 *
 * @brief              - This function for configuring interrupt
 *
 * @param[in]          - IRQ Number
 * @param[in]          - ENABLE or DISABLE macros
 *
 * @return             - none
 *
 * @note               - none
 */
void SPI_InterruptConfig(uint8_t IRQNumber  , uint8_t EnorDi)
{

}


/***************************************************
 * @fun                - SPI_PriorityConfig
 *
 * @brief              - This function for configuring interrupt priority
 *
 * @param[in]          - IRQ Priority
 * @return             - none
 *
 * @note               - none
 */
void SPI_PriorityConfig(uint8_t IRQNumber , uint32_t IRQPriority)
{

}


/***************************************************
 * @fun                - SPI_IRQHandling
 *
 * @brief              - This function Handles IRQ
 *
 * @param[in]          - Base address of SPI Peripheral
 *
 * @return             - none
 *
 * @note               - none
 */
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{

}

