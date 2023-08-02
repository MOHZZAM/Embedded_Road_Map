/*
 * STM32F207ZGxx.h
 *
 *  Created on: Jul 2, 2023
 *      Author: moazzam
 */

#ifndef INC_STM32F207ZGXX_H_
#define INC_STM32F207ZGXX_H_

#include <string.h>
#include <stdint.h>


#define __vo                     volatile


/***********************************START:Processor Specific Details************************/
/*
 * ARM cortex M3 processor NVIC ISER register addresses
 */
#define NVIC_ISER0             ((__vo uint32_t *)(0xE000E100))
#define NVIC_ISER1             ((__vo uint32_t *)(0xE000E104))
#define NVIC_ISER2             ((__vo uint32_t *)(0xE000E108))
#define NVIC_ISER3             ((__vo uint32_t *)(0xE000E10C))

/*
 * ARM cortex M3 processor NVIC ICER register addresses
 */
#define NVIC_ICER0             ((__vo uint32_t *)(0XE000E180))
#define NVIC_ICER1             ((__vo uint32_t *)(0XE000E184))
#define NVIC_ICER2             ((__vo uint32_t *)(0XE000E188))
#define NVIC_ICER3             ((__vo uint32_t *)(0XE000E18C))

/*
 * ARM cortex M3 processor NVIC IPR register addresses
 */
#define NVIC_IPR              ((__vo uint32_t *)(0xE000E400))


#define NO_PR_BITS_IMPLEMENTED              4

/*
 *base addresses of ROM and RAM
 */

#define FLASH_BASE_ADDR        (0X08000000U)
#define SRAM_BASE_ADDR         (0x20000000U)

/*
 *base addresses of different busses
 */

#define PERIPH_BASE            (0X40000000U)
#define APB1_BASE_ADDR         (PERIPH_BASE)
#define APB2_BASE_ADDR         (0x40010000U)
#define AHB1_BASE_ADDR         (0x40020000U)
#define AHB2_BASE_ADDR         (0x50000000U)


/*
 *base addresses of PERPHERALS hanging on APB1 BUS
 */

#define TIM2_BASE_ADDR         (APB1_BASE_ADDR + 0X0000U)
#define TIM3_BASE_ADDR         (APB1_BASE_ADDR + 0x0400U)
#define TIM4_BASE_ADDR         (APB1_BASE_ADDR + 0x0800U)
#define TIM5_BASE_ADDR         (APB1_BASE_ADDR + 0x0C00U)
#define TIM6_BASE_ADDR         (APB1_BASE_ADDR + 0x1000U)
#define TIM7_BASE_ADDR         (APB1_BASE_ADDR + 0x1400U)
#define TIM12_BASE_ADDR        (APB1_BASE_ADDR + 0x1800U)
#define TIM13_BASE_ADDR        (APB1_BASE_ADDR + 0x1C00U)
#define TIM14_BASE_ADDR        (APB1_BASE_ADDR + 0x2000U)

#define SPI2_BASE_ADDR         (APB1_BASE_ADDR + 0X3800U)
#define SPI3_BASE_ADDR         (APB1_BASE_ADDR + 0x3C00U)

#define USART2_BASE_ADDR       (APB1_BASE_ADDR + 0x4400U)
#define USART3_BASE_ADDR       (APB1_BASE_ADDR + 0x4800U)
#define UART4_BASE_ADDR        (APB1_BASE_ADDR + 0x4C00U)
#define UART5_BASE_ADDR        (APB1_BASE_ADDR + 0x5000U)

#define I2C1_BASE_ADDR         (APB1_BASE_ADDR + 0x5400U)
#define I2C2_BASE_ADDR         (APB1_BASE_ADDR + 0x5800U)
#define I2C3_BASE_ADDR         (APB1_BASE_ADDR + 0x5C00U)

#define CAN1_BASE_ADDR         (APB1_BASE_ADDR + 0x6800U)
#define CAN2_BASE_ADDR         (APB1_BASE_ADDR + 0x6400U)

#define PWR_BASE_ADDR          (APB1_BASE_ADDR + 0x7000U)

#define DAC_BASE_ADDR          (APB1_BASE_ADDR + 0x7400U)

/*
 *base addresses of PERPHERALS hanging on APB2 BUS
 */

#define TIM1_BASE_ADDR         (APB2_BASE_ADDR + 0X0000U)
#define TIM8_BASE_ADDR         (APB2_BASE_ADDR + 0x0400U)

#define USART1_BASE_ADDR       (APB2_BASE_ADDR + 0X1000U)
#define USART6_BASE_ADDR       (APB2_BASE_ADDR + 0x1400U)

#define ADC_BASE_ADDR          (APB2_BASE_ADDR + 0x2000U)

#define SPI1_BASE_ADDR         (APB2_BASE_ADDR + 0X3000U)

#define SYSCFG_BASE_ADDR       (APB2_BASE_ADDR + 0x3800U)

#define EXTI_BASE_ADDR         (APB2_BASE_ADDR + 0x3C00U)

#define TIM10_BASE_ADDR        (APB2_BASE_ADDR + 0X4800U)
#define TIM11_BASE_ADDR        (APB2_BASE_ADDR + 0x4400U)

/*
 *base addresses of PERPHERALS hanging on AHB1
 */

#define GPIOA_BASE_ADDR        (AHB1_BASE_ADDR + 0x0000U)
#define GPIOB_BASE_ADDR        (AHB1_BASE_ADDR + 0x0400U)
#define GPIOC_BASE_ADDR        (AHB1_BASE_ADDR + 0x0800U)
#define GPIOD_BASE_ADDR        (AHB1_BASE_ADDR + 0x0C00U)
#define GPIOE_BASE_ADDR        (AHB1_BASE_ADDR + 0x1000U)
#define GPIOF_BASE_ADDR        (AHB1_BASE_ADDR + 0x1400U)
#define GPIOG_BASE_ADDR        (AHB1_BASE_ADDR + 0x1800U)
#define GPIOH_BASE_ADDR        (AHB1_BASE_ADDR + 0x1C00U)
#define GPIOI_BASE_ADDR        (AHB1_BASE_ADDR + 0x2000U)

#define RCC_BASE_ADDR          (AHB1_BASE_ADDR + 0x3800U)

/*
 * Defining gpio registers structure
 * pls note all controllers have different no of register for gpio
 * so always read RM
 */
typedef struct
{
	__vo uint32_t MODER;               /*!GPIO port mode register              ,  Address offset: 0x00 */
	__vo uint32_t OTYPER;              /*!GPIO port output type register       ,  Address offset: 0x04*/
	__vo uint32_t OSPEEDR;             /*!GPIO port output speed register      ,  Address offset: 0x08 */
	__vo uint32_t PUPDR;               /*!GPIO port pull-up/pull-down register ,  Address offset: 0x0C*/
	__vo uint32_t IDR;                 /*!GPIO port input data register        ,  Address offset: 0x10 */
	__vo uint32_t ODR;                 /*!GPIO port output data register       ,  Address offset: 0x14 */
	__vo uint32_t BSRR;                /*!GPIO port bit set/reset register     ,  Address offset: 0x18 */
	__vo uint32_t LCKR;                /*!GPIO port configuration lock register,  Address offset: 0x1C */
	__vo uint32_t AFRL;                /*!GPIO alternate function low register ,  Address offset: 0x20 */
	__vo uint32_t AFRH;                /*!GPIO alternate function high register,  Address offset: 0x24 */

}GPIO_RegDef_t;


/*
 * Defining RCC registers structure
 * pls note all controllers have different no of register for gpio
 * so always read RM
 */

typedef struct
{
	__vo uint32_t CR;                  /*!RCC clock control register           ,  Address offset: 0x00 */
	__vo uint32_t PLLCFG;              /*!RCC PLL configuration register       ,  Address offset: 0x04*/
	__vo uint32_t CFGR;                /*!RCC clock configuration register     ,  Address offset: 0x08 */
	__vo uint32_t CIR;                 /*!RCC clock interrupt register         ,  Address offset: 0x0C*/
	__vo uint32_t AHB1RSTR;            /*!RCC AHB1 peripheral reset register   ,  Address offset: 0x10 */
	__vo uint32_t AHB2RSTR;            /*!RCC AHB2 peripheral reset register   ,  Address offset: 0x14 */
	__vo uint32_t AHB3RSTR;            /*!RCC AHB2 peripheral reset register   ,  Address offset: 0x18 */
    uint32_t Reserved1;
	__vo uint32_t APB1RSTR;            /*!RCC APB1 peripheral reset register   ,  Address offset: 0x20 */
	__vo uint32_t APB2RSTR;            /*!RCC APB2 peripheral reset register   ,  Address offset: 0x24 */
	 uint32_t Reserved2[2];
	__vo uint32_t AHB1ENR;             /*!RCC AHB1 peripheral clock enable register ,  Address offset: 0x30 */
	__vo uint32_t AHB2ENR;             /*!RCC AHB2 peripheral clock enable register ,  Address offset: 0x34 */
	__vo uint32_t AHB3ENR;             /*!RCC AHB2 peripheral clock enable register ,  Address offset: 0x38 */
	 uint32_t Reserved3;
	__vo uint32_t APB1ENR;             /*!RCC APB1 peripheral clock enable register ,  Address offset: 0x40 */
	__vo uint32_t APB2ENR;             /*!RCC APB2 peripheral clock enable register ,  Address offset: 0x44 */
	 uint32_t Reserved4[2];
	__vo uint32_t AHB1LPENR;           /*!RCC AHB1 peripheral clock enable in low power mode register ,  Address offset: 0x50 */
	__vo uint32_t AHB2LPENR;           /*!RCC AHB2 peripheral clock enable in low power mode register ,  Address offset: 0x54 */
	__vo uint32_t AHB3LPENR;           /*!RCC AHB2 peripheral clock enable in low power mode register ,  Address offset: 0x58 */
	 uint32_t Reserved5;
	__vo uint32_t APB1LPENR;           /*!RCC APB1 peripheral clock enable in low power mode register ,  Address offset: 0x60 */
	__vo uint32_t APB2LPENR;           /*!RCC APB2 peripheral clock enabled in low power mode register,  Address offset: 0x64 */
	 uint32_t Reserved6[2];
	__vo uint32_t BDCR;                /*!RCC Backup domain control register  ,  Address offset: 0x70 */
	__vo uint32_t CSR;                 /*!RCC clock control & status register ,  Address offset: 0x74 */
	 uint32_t Reserved7[2];
	__vo uint32_t SSCGR;               /*!RCC spread spectrum clock generation register  ,  Address offset: 0x80 */
	__vo uint32_t PLLI2SCFGR;          /*!RCC PLLI2S configuration register   ,  Address offset: 0x84 */


}RCC_RegDef_t;


/*
 * Defining EXTI registers structure
 * pls note all controllers have different no of register for gpio
 * so always read RM
 */
typedef struct
{
	__vo uint32_t IMR;                 /*!Interrupt mask register                   ,  Address offset: 0x00 */
	__vo uint32_t EMR;                 /*!Event mask register                       ,  Address offset: 0x04 */
	__vo uint32_t RTSR;                /*!Rising trigger selection register         ,  Address offset: 0x08 */
	__vo uint32_t FTSR;                /*!Falling trigger selection register        ,  Address offset: 0x0C */
	__vo uint32_t SWIER;               /*!Software interrupt event register         ,  Address offset: 0x10 */
	__vo uint32_t PR;                  /*!Pending register                          ,  Address offset: 0x14 */
}EXTI_RegDef_t;


/*
 * Defining EXTI registers structure
 * pls note all controllers have different no of register for gpio
 * so always read RM
 */
typedef struct
{
	__vo uint32_t MEMRMP;              /*!SYSCFG memory remap register              ,  Address offset: 0x00 */
	__vo uint32_t PMC;                 /*!SYSCFG peripheral mode configuration register         ,  Address offset: 0x04 */
	__vo uint32_t EXTICR[4];           /*!SYSCFG external interrupt configuration register 1-4    ,  Address offset: 0x08 - 0x14 */
	uint32_t Reserved1[2];
	__vo uint32_t CMPCR;               /*!Compensation cell control register        ,  Address offset: 0x20 */

}SYSCFG_RegDef_t;

/*
 * Defining SPI registers structure
 * pls note all controllers have different no of register for SPI
 * so always read RM
 */
typedef struct
{
	__vo uint32_t CR1;                 /*!SPI control register 1                    ,  Address offset: 0x00 */
	__vo uint32_t CR2;                 /*!SPI control register 2                    ,  Address offset: 0x04 */
	__vo uint32_t SR;                  /*!SPI status register                       ,  Address offset: 0x08 */
	__vo uint32_t DR;                  /*!SPI data register                         ,  Address offset: 0x0C */
	__vo uint32_t CRCPR;               /*!SPI CRC polynomial register               ,  Address offset: 0x10 */
	__vo uint32_t RXCRCR;              /*!SPI RX CRC register                       ,  Address offset: 0x14 */
	__vo uint32_t TXCRCR;              /*!SPI TX CRC register                       ,  Address offset: 0x18 */
	__vo uint32_t I2SCFGR;             /*!SPI_I2S configuration register            ,  Address offset: 0x1C */
	__vo uint32_t I2SPR;               /*!SPI_I2S prescaler register                ,  Address offset: 0x20 */

}SPI_RegDef_t;


/*
 * Peripheral definitions for GPIO
 */

#define GPIOA                  ((GPIO_RegDef_t *)GPIOA_BASE_ADDR)
#define GPIOB                  ((GPIO_RegDef_t *)GPIOB_BASE_ADDR)
#define GPIOC                  ((GPIO_RegDef_t *)GPIOC_BASE_ADDR)
#define GPIOD                  ((GPIO_RegDef_t *)GPIOD_BASE_ADDR)
#define GPIOE                  ((GPIO_RegDef_t *)GPIOE_BASE_ADDR)
#define GPIOF                  ((GPIO_RegDef_t *)GPIOF_BASE_ADDR)
#define GPIOG                  ((GPIO_RegDef_t *)GPIOG_BASE_ADDR)
#define GPIOH                  ((GPIO_RegDef_t *)GPIOH_BASE_ADDR)
#define GPIOI                  ((GPIO_RegDef_t *)GPIOI_BASE_ADDR)

#define RCC                    ((RCC_RegDef_t *)RCC_BASE_ADDR)

#define EXTI                   ((EXTI_RegDef_t *)EXTI_BASE_ADDR)

#define SYSCFG                 ((SYSCFG_RegDef_t *)SYSCFG_BASE_ADDR)

#define SPI1                   ((SPI_RegDef_t *)SPI1_BASE_ADDR)
#define SPI2                   ((SPI_RegDef_t *)SPI2_BASE_ADDR)
#define SPI3                   ((SPI_RegDef_t *)SPI3_BASE_ADDR)

/*
 * Clock enable macros for GPIO
 */
#define GPIOA_PCLK_EN()        (RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()        (RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()        (RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()        (RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()        (RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN()        (RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()        (RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()        (RCC->AHB1ENR |= (1<<7))
#define GPIOI_PCLK_EN()        (RCC->AHB1ENR |= (1<<8))

/*
 * Clock enable macros for SPI
 */
#define SPI1_PCLK_EN()         (RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()         (RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()         (RCC->APB1ENR |= (1<<15))

/*
 * Clock enable macros for I2C
 */
#define I2C1_PCLK_EN()         (RCC->APB1ENR |= (1<<19))
#define I2C2_PCLK_EN()         (RCC->APB1ENR |= (1<<20))
#define I2C3_PCLK_EN()         (RCC->APB1ENR |= (1<<21))

/*
 * Clock enable macros for USART
 */
#define USART1_PCLK_EN()       (RCC->APB2ENR |= (1<<3))
#define USART2_PCLK_EN()       (RCC->APB1ENR |= (1<<15))
#define USART3_PCLK_EN()       (RCC->APB1ENR |= (1<<16))
#define UART4_PCLK_EN()        (RCC->APB1ENR |= (1<<17))
#define UART5_PCLK_EN()        (RCC->APB1ENR |= (1<<18))
#define USART6_PCLK_EN()       (RCC->APB2ENR |= (1<<4))

/*
 * Clock enable macros for SYSCONFIG
 */
#define SYSCFG_PCLK_EN()       (RCC->APB2ENR |= (1<<14))


/*
 * Clock disable macros for GPIO
 */
#define GPIOA_PCLK_DI()        (RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()        (RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()        (RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()        (RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()        (RCC->AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI()        (RCC->AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI()        (RCC->AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI()        (RCC->AHB1ENR &= ~(1<<7))
#define GPIOI_PCLK_DI()        (RCC->AHB1ENR &= ~(1<<8))

/*
 * Clock disable macros for SPI
 */
#define SPI1_PCLK_DI()         (RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI()         (RCC->APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI()         (RCC->APB1ENR &= ~(1<<15))

/*
 * Clock disable macros for I2C
 */
#define I2C1_PCLK_DI()         (RCC->APB1ENR &= ~(1<<19))
#define I2C2_PCLK_DI()         (RCC->APB1ENR &= ~(1<<20))
#define I2C3_PCLK_DI()         (RCC->APB1ENR &= ~(1<<21))

/*
 * Clock disable macros for USART
 */
#define USART1_PCLK_DI()       (RCC->APB2ENR &= ~(1<<3))
#define USART2_PCLK_DI()       (RCC->APB1ENR &= ~(1<<15))
#define USART3_PCLK_DI()       (RCC->APB1ENR &= ~(1<<16))
#define UART4_PCLK_DI()        (RCC->APB1ENR &= ~(1<<17))
#define UART5_PCLK_DI()        (RCC->APB1ENR &= ~(1<<18))
#define USART6_PCLK_DI()       (RCC->APB2ENR &= ~(1<<4))

/*
 * Clock disable macros for SYSCONFIG
 */
#define SYSCFG_PCLK_DI()       (RCC->APB2ENR &= ~(1<<12))


/*
 * Macros to reset GPIO peripherals
 */
#define GPIOA_REG_RESET()      do{(RCC->AHB1RSTR |= (1<<0)); (RCC->AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOB_REG_RESET()      do{(RCC->AHB1RSTR |= (1<<1)); (RCC->AHB1RSTR &= ~(1<<1)); }while(0)
#define GPIOC_REG_RESET()      do{(RCC->AHB1RSTR |= (1<<2)); (RCC->AHB1RSTR &= ~(1<<2)); }while(0)
#define GPIOD_REG_RESET()      do{(RCC->AHB1RSTR |= (1<<3)); (RCC->AHB1RSTR &= ~(1<<3)); }while(0)
#define GPIOE_REG_RESET()      do{(RCC->AHB1RSTR |= (1<<4)); (RCC->AHB1RSTR &= ~(1<<4)); }while(0)
#define GPIOF_REG_RESET()      do{(RCC->AHB1RSTR |= (1<<5)); (RCC->AHB1RSTR &= ~(1<<5)); }while(0)
#define GPIOG_REG_RESET()      do{(RCC->AHB1RSTR |= (1<<6)); (RCC->AHB1RSTR &= ~(1<<6)); }while(0)
#define GPIOH_REG_RESET()      do{(RCC->AHB1RSTR |= (1<<7)); (RCC->AHB1RSTR &= ~(1<<7)); }while(0)
#define GPIOI_REG_RESET()      do{(RCC->AHB1RSTR |= (1<<8)); (RCC->AHB1RSTR &= ~(1<<8)); }while(0)

/*
 * Macros to reset SPI peripherals
 */
#define SPI1_REG_RESET()       do{(RCC->APB2RSTR |= (1<<12)); (RCC->APB2RSTR &= ~(1<<10)); }while(0)
#define SPI2_REG_RESET()       do{(RCC->APB1RSTR |= (1<<14)); (RCC->APB1RSTR &= ~(1<<12)); }while(0)
#define SPI3_REG_RESET()       do{(RCC->APB1RSTR |= (1<<15)); (RCC->APB1RSTR &= ~(1<<13)); }while(0)

/*
 * return gpio port code for syscfg
 */
#define GPIO_BASEADDR_TO_CODE(x) ( (x == GPIOA) ? 0 :\
		                           (x == GPIOB) ? 1 :\
			                   	   (x == GPIOC) ? 2 :\
					           	   (x == GPIOD) ? 3 :\
					           	   (x == GPIOE) ? 4 :\
								   (x == GPIOF) ? 5 :\
								   (x == GPIOG) ? 6 :\
								   (x == GPIOH) ? 7 :\
					           	   (x == GPIOI) ? 8 :0 )

/*
 * IRQ number for stm32f401xx MCU
 * NOTE: update these macros with valid values according to your MCU
 */
#define IRQ_NO_EXTI0           6
#define IRQ_NO_EXTI1           7
#define IRQ_NO_EXTI2           8
#define IRQ_NO_EXTI3           9
#define IRQ_NO_EXTI4           10
#define IRQ_NO_EXTI9_5         23
#define IRQ_NO_EXTI15_10       40


//some generic Macros
#define ENABLE                 1
#define DISABLE                0
#define SET                    ENABLE
#define RESET                  DISABLE
#define GPIO_PIN_SET           SET
#define GPIO_PIN_RESET         RESET
#define FLAG_SET               SET
#define FLAG_RESET             RESET



/******************************************************************
 * Bit position definition for SPI peripheral
 *******************************************************************/
#define SPI_CR1_CPHA         0
#define SPI_CR1_CPOL         1
#define SPI_CR1_MSTR         2
#define SPI_CR1_BR           3
#define SPI_CR1_SPE          6
#define SPI_CR1_LSB_FIRST    7
#define SPI_CR1_SSI          8
#define SPI_CR1_SSM          9
#define SPI_CR1_RX_ONLY      10
#define SPI_CR1_DFF          11
#define SPI_CR1_CRC_NEXT     12
#define SPI_CR1_CRC_EN       13
#define SPI_CR1_BIDI_OE      14
#define SPI_CR1_BIDI         15


#define SPI_CR2_RXDMAEN      0
#define SPI_CR2_TXDMAEN      1
#define SPI_CR2_SSOE         2
#define SPI_CR2_FRF          4
#define SPI_CR2_ERRIE        5
#define SPI_CR2_RXNEIE       6
#define SPI_CR2_TXEIE        7



#define SPI_SR_RXNE          0
#define SPI_SR_TXE           1
#define SPI_SR_CHSIDE        2
#define SPI_SR_UDR           3
#define SPI_SR_CRC_ERR       4
#define SPI_SR_MODF          5
#define SPI_SR_OVR           6
#define SPI_SR_BSY           7
#define SPI_SR_FRE           8


#endif /* INC_STM32F207ZGXX_H_ */
