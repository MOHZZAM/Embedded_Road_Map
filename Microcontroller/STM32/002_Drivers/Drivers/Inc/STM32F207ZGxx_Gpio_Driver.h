/*
 * STM32F207ZGxx_Gpio_Driver.h
 *
 *  Created on: Jul 2, 2023
 *      Author: moazzam
 */

#ifndef INC_STM32F207ZGXX_GPIO_DRIVER_H_
#define INC_STM32F207ZGXX_GPIO_DRIVER_H_

#include "STM32F207ZGxx.h"

/*
 * Creating configuration structure for gpio pin
 */
typedef struct
{
	uint8_t GPIO_PinNumber;         /*!<possible values from @GPIO_PIN_NUMBERS>*/
	uint8_t GPIO_PinMode;           /*!<possible values from @GPIO_PIN_MODES>*/
	uint8_t GPIO_PinSpeed;          /*!<possible values from @GPIO_PIN_SPEED>*/
	uint8_t GPIO_PinPuPdControl;    /*!<possible values from @GPIO_PIN_OUTPUT_TYPE>*/
	uint8_t GPIO_PinOPType;         /*!<possible values from @GPIO_PIN_PUPD>*/
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;
/*
 * Creating gpio handle structure for gpio pin
 */
typedef struct
{

	GPIO_RegDef_t *pGPIOx;  /*!<pointer to hold base address of gpio peripheral to which pin belongs>*/
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * GPIO PIN possible NUMBERS
 */
#define GPIO_PIN_NO_0                  0
#define GPIO_PIN_NO_1                  1
#define GPIO_PIN_NO_2                  2
#define GPIO_PIN_NO_3                  3
#define GPIO_PIN_NO_4                  4
#define GPIO_PIN_NO_5                  5
#define GPIO_PIN_NO_6                  6
#define GPIO_PIN_NO_7                  7
#define GPIO_PIN_NO_8                  8
#define GPIO_PIN_NO_9                  9
#define GPIO_PIN_NO_10                 10
#define GPIO_PIN_NO_11                 11
#define GPIO_PIN_NO_12                 12
#define GPIO_PIN_NO_13                 13
#define GPIO_PIN_NO_14                 14
#define GPIO_PIN_NO_15                 15

/*
 * @GPIO_PIN_MODES
 * GPIO PIN possible modes
 */
#define GPIO_MODE_IN                   0
#define GPIO_MODE_OU                   1
#define GPIO_MODE_ALTFN                2
#define GPIO_MODE_ANALOG               3
#define GPIO_MODE_IT_FT                4
#define GPIO_MODE_IT_RT                5
#define GPIO_MODE_IT_RFT               6


/*
 * @GPIO_PIN_OUTPUT_TYPE
 * GPIO PIN possible output type
 */
#define GPIO_OP_PP                     0
#define GPIO_OP_OD                     1


/*
 * @GPIO_PIN_SPEED
 * GPIO PIN possible SPEEDS
 */
#define GPIO_SPEED_LOW                 0
#define GPIO_SPEED_MEDIUM              1
#define GPIO_SPEED_HIGH                2
#define GPIO_SPEED_VERYHIGH            3

/*
 * @GPIO_PIN_PUPD
 * GPIO PIN puLL up and pull down configuration macros
 */
#define GPIO_NO_PUPD                   0
#define GPIO_PIN_PU                    1
#define GPIO_PIN_PD                    2


/*******************************************************************
 *                        APIs supported by this driver
 *                   for more information check APIs definition
 *******************************************************************/

/*
 * GPIO Peripheral clock API
 */
void GPIO_PeriClkCntrl(GPIO_RegDef_t *pGPIOx , uint8_t EnorDi);

/*
 * GPIO Init APIs
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * GPIO read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx , uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx , uint8_t PinNumber , uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx , uint16_t value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx , uint8_t PinNumber);

/*
 * GPIO ISR handling
 */
void GPIO_InterruptConfig(uint8_t IRQNumber  , uint8_t EnorDi);
void GPIO_PriorityConfig(uint8_t IRQNumber , uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32F207ZGXX_GPIO_DRIVER_H_ */
