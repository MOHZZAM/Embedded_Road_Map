/*
 * STM32F207ZGxx_SPI_Driver.h
 *
 *  Created on: Jul 2, 2023
 *      Author: moazzam
 */

#ifndef INC_STM32F207ZGXX_SPI_DRIVER_H_
#define INC_STM32F207ZGXX_SPI_DRIVER_H_

#include "STM32F207ZGxx.h"

/*
 * Configuration structure for SPI
 */
typedef struct
{
	uint8_t SPI_DeviceMode;            /*!<possible values for @SPI_DeviceMode>*/
	uint8_t SPI_BusConfig;             /*!<possible values for @SPI_BusConfig>*/
	uint8_t SPI_SclkSpeed;             /*!<possible values for @SPI_SclkSpeed>*/
	uint8_t SPI_DFF;                   /*!<possible values for @SPI_DFF>*/
	uint8_t SPI_CPHA;                  /*!<possible values for @SPI_CPHA>*/
	uint8_t SPI_CPOL;                  /*!<possible values for @SPI_CPOL>*/
	uint8_t SPI_SSM;                   /*!<possible values for @SPI_SSM>*/
}SPI_Config_t;

/*
 * SPI Handle
 */
typedef struct
{
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPIConfig;
}SPI_Handle_t;


/*
 * @SPI_DeviceMode
 * SPI POSSIBLE MODES
 */
#define SPI_DEVICE_MODE_MASTER         1
#define SPI_DEVICE_MODE_SLAVE          0


/*
 * @SPI_BusConfig
 * SPI POSSIBLE BUS CONFIGURATION
 */
#define SPI_BUS_CONFIG_FD              1
#define SPI_BUS_CONFIG_HD              2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY  3


/*
 * @SPI_SclkSpeed
 * SPI POSSIBLE CLOCK SPEED CONFIGURATION
 */
#define SPI_SCLK_SPEED_DIV2            0
#define SPI_SCLK_SPEED_DIV4            1
#define SPI_SCLK_SPEED_DIV8            2
#define SPI_SCLK_SPEED_DIV16           3
#define SPI_SCLK_SPEED_DIV32           4
#define SPI_SCLK_SPEED_DIV64           5
#define SPI_SCLK_SPEED_DIV128          6
#define SPI_SCLK_SPEED_DIV256          7


/*
 * @SPI_DFF
 * SPI POSSIBLE DATA FRAME BIT CONFIGURATION
 */
#define SPI_DFF_8BIT                   0
#define SPI_DFF_16BIT                  1


/*
 * @SPI_CPHA
 * SPI POSSIBLE CLOCK PHASES
 */
#define SPI_CPHA_LOW                   0
#define SPI_CPHA_HIGH                  1


/*
 * @SPI_CPOL
 * SPI POSSIBLE CLOCK POLARITYS
 */
#define SPI_CPOL_IDLE_LOW              0
#define SPI_CPOL_IDLE_HIGH             1


/*
 * @SPI_SSM
 * SPI POSSIBLE DATA FRAME BIT CONFIGURATION
 */
#define SPI_SSM_DI                     0
#define SPI_SSM_EN                     1


/*
 * SPI related flag definitions
 */
#define SPI_TXE_FLAG               (1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG              (1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG              (1 << SPI_SR_BSY)


/*
 * SPI Peripheral clock API
 */
void SPI_PeriClkCntrl(SPI_RegDef_t *pSPIx , uint8_t EnorDi);


/*
 * SPI Init APIs
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);


/*
 * SPI data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx , uint8_t *pTxBuffer , uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx , uint8_t *pRxBuffer , uint32_t Len);


/*
 * SPI ISR handling
 */
void SPI_InterruptConfig(uint8_t IRQNumber  , uint8_t EnorDi);
void SPI_PriorityConfig(uint8_t IRQNumber , uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);


/*
 * Other functions
 */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName);
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx , uint8_t EnorDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx , uint8_t EnorDi);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx , uint8_t EnorDi);


#endif /* INC_STM32F207ZGXX_SPI_DRIVER_H_ */
