/*
 * STM32F207ZGxx_Gpio_Driver.c
 *
 *  Created on: Jul 2, 2023
 *      Author: moazzam
 */


#include "STM32F207ZGxx_Gpio_Driver.h"

/*
 * GPIO Peripheral clock API
 */

/***************************************************
 * @fun                - GPIO_PeriClkCntrl
 *
 * @brief              - This function Enable or Disable clock of particular GPIO port
 *
 * @param[in]          - Base address of GPIO peripheral
 * @param[in]          - ENABLE or DISABLE macros
 *
 * @return             - none
 *
 * @note               - none
 */
void GPIO_PeriClkCntrl(GPIO_RegDef_t *pGPIOx , uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (pGPIOx == GPIOA) GPIOA_PCLK_EN();
		else if (pGPIOx == GPIOB) GPIOB_PCLK_EN();
		else if (pGPIOx == GPIOC) GPIOC_PCLK_EN();
		else if (pGPIOx == GPIOD) GPIOD_PCLK_EN();
		else if (pGPIOx == GPIOE) GPIOE_PCLK_EN();
		else if (pGPIOx == GPIOH) GPIOH_PCLK_EN();
		else {}


	}
	else
	{
		if (pGPIOx == GPIOA) GPIOA_PCLK_DI();
		else if (pGPIOx == GPIOB) GPIOB_PCLK_DI();
		else if (pGPIOx == GPIOC) GPIOC_PCLK_DI();
		else if (pGPIOx == GPIOD) GPIOD_PCLK_DI();
		else if (pGPIOx == GPIOE) GPIOE_PCLK_DI();
		else if (pGPIOx == GPIOH) GPIOH_PCLK_DI();
		else {}
	}
}

/*
 * GPIO Init APIs
 */

/*
 * GPIO Peripheral clock API
 */

/***************************************************
 * @fun                - GPIO_Init
 *
 * @brief              - This function initializes particular GPIO port
 *
 * @param[in]          - Base address of GPIO Handle
 *
 * @return             - none
 *
 * @note               - none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp =0;

	//Peripheral clock enable
	GPIO_PeriClkCntrl(pGPIOHandle->pGPIOx, ENABLE);

	// 1. configuring pin mode
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode) << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Resetting
		pGPIOHandle->pGPIOx->MODER |= temp; //setting
		temp = 0;
	}
	else
	{
		//do it later
		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//1. configure FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clearing RTSR
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//1. configure RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clearing RTSR
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//1. configure both FTSR and RTSR
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		//2. configure GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
        SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] |= (portcode << (4*temp2));

		//3. Enable exti interrupt delivery using exti_imr
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	// 2. configuring pin speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed) << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Resetting
	pGPIOHandle->pGPIOx->OSPEEDR |= temp; //Setting
	temp = 0;

	//3. configure pull up and pull down
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl) << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Resetting
	pGPIOHandle->pGPIOx->PUPDR |= temp; //Setting
	temp = 0;

	//4. configure output type
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType) << ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Resetting
	pGPIOHandle->pGPIOx->OTYPER |= temp; //Setting
	temp = 0;

	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		// 5. configure alt function register
		uint8_t temp1;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%8;

		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode) << (4 * temp1);

		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber < 8)
		{
			pGPIOHandle->pGPIOx->AFRL &= ~(0xf << (4*temp1)); //Resetting
			pGPIOHandle->pGPIOx->AFRL |= temp; //Setting
		}
		else
		{
			pGPIOHandle->pGPIOx->AFRH &= ~(0xf << (4*temp1)); //Resetting
			pGPIOHandle->pGPIOx->AFRH |= temp; //Setting
		}

		temp = 0;

	}

}

/***************************************************
 * @fun                - GPIO_DeInit
 *
 * @brief              - This function de-initializes particular GPIO port
 *
 * @param[in]          - Base address of GPIO peripheral
 *
 * @return             - none
 *
 * @note               - none
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if (pGPIOx == GPIOA) GPIOA_PCLK_EN();
	else if (pGPIOx == GPIOB) GPIOA_REG_RESET();
	else if (pGPIOx == GPIOC) GPIOA_REG_RESET();
	else if (pGPIOx == GPIOD) GPIOA_REG_RESET();
	else if (pGPIOx == GPIOE) GPIOA_REG_RESET();
	else if (pGPIOx == GPIOH) GPIOA_REG_RESET();
	else {}

}

/*
 * GPIO read and write
 */


/***************************************************
 * @fun                - GPIO_ReadFromInputPin
 *
 * @brief              - This function read from input pin of particular port
 *
 * @param[in]          - Base address of GPIO Peripheral
 * @param[in]          - Pin number of particular port
 *
 * @return             - Return 1 or 0
 *
 * @note               - none
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx , uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & (0x00000001));
	return value;

}

/***************************************************
 * @fun                - GPIO_ReadFromInputPort
 *
 * @brief              - This function read particular port
 *
 * @param[in]          - Base address of GPIO Peripheral
 *
 * @return             - Return value of port
 *
 * @note               - none
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)(pGPIOx->IDR );
	return value;

}

/***************************************************
 * @fun                - GPIO_WriteToOutputPin
 *
 * @brief              - This function write pin of particular port
 *
 * @param[in]          - Base address of GPIO Peripheral
 * @param[in]          - Pin number of particular port
 * @param[in]          - GPIO_SET_PIN or GPIO_RESET_PIN macros
 *
 * @return             - none
 *
 * @note               - none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx , uint8_t PinNumber , uint8_t value)
{
	if (value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1<<PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1<<PinNumber);
	}

}

/***************************************************
 * @fun                - GPIO_WriteToOutputPort
 *
 * @brief              - This function write a port
 *
 * @param[in]          - Base address of GPIO Peripheral
 * @param[in]          - Pin number of particular port
 * @param[in]          - GPIO_SET_PIN or GPIO_RESET_PIN
 *
 * @return             - none
 *
 * @note               - none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx , uint16_t value)
{
	pGPIOx->ODR = value;
}

/***************************************************
 * @fun                - GPIO_ToggleOutputPin
 *
 * @brief              - This function toggles pin of particular port
 *
 * @param[in]          - Base address of GPIO Peripheral
 * @param[in]          - Pin number of particular port
 *
 * @return             - none
 *
 * @note               - none
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx , uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1<<PinNumber);

}

/*
 * GPIO ISR handling
 */

/***************************************************
 * @fun                - GPIO_InterruptConfig
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
void GPIO_InterruptConfig(uint8_t IRQNumber , uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			//program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			//program ISER3 register
			*NVIC_ISER3 |= (1 << (IRQNumber % 64));
		}
	}
	else
	{
		if (IRQNumber <= 31)
		{
			//program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			//program ICER1 register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			//program ICER3 register
			*NVIC_ICER3 |= (1 << (IRQNumber % 64));
		}
	}

}


/***************************************************
 * @fun                - GPIO_PriorityConfig
 *
 * @brief              - This function for configuring interrupt priority
 *
 * @param[in]          - IRQ Priority
 * @return             - none
 *
 * @note               - none
 */
void GPIO_PriorityConfig(uint8_t IRQNumber , uint32_t IRQPriority)
{
	uint8_t iprx = IRQNumber/4;
	uint8_t iprx_section = IRQNumber%4;
	uint8_t shift_amount = (8*iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_IPR + (iprx)) |= (IRQPriority << shift_amount);

}


/***************************************************
 * @fun                - GPIO_IRQHandling
 *
 * @brief              - This function Handles IRQ
 *
 * @param[in]          - Pin Number
 *
 * @return             - none
 *
 * @note               - none
 */
void GPIO_IRQHandling(uint8_t PinNumber)
{
	if ((EXTI->PR) & (1<<PinNumber))
	{
		EXTI->PR |= (1 << PinNumber);
	}

}
