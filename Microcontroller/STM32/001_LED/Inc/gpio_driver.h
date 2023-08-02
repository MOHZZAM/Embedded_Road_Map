/*
 * main.h
 *
 *  Created on: Apr 15, 2023
 *      Author: md mohzzam
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_


#define SET   (1)
#define CLEAR (0)

#define gpio_port_b_clock_enable       (uint32_t*)(0x40023800 + 0x30)
#define gpio_port_b_mode_register      (uint32_t*)(0x40020400)
#define gpio_port_b_output_register    (uint32_t*)(0x40020400 + 0x14)

typedef struct{

	uint32_t GPIOAEN            :1;
	uint32_t GPIOBEN            :1;
	uint32_t GPIOCEN            :1;
	uint32_t GPIODEN            :1;
	uint32_t RESERVED1          :2;
	uint32_t GPIOH_EN           :1;
	uint32_t RESERVED2          :4;
	uint32_t CRCEN              :2;
	uint32_t RESERVED3          :8;
	uint32_t DMA1EN             :1;
	uint32_t DMA2EN             :1;
	uint32_t RESERVED4          :9;

}RCC_AHB1ENR_t;


typedef struct{

	uint32_t PIN0               :2;
	uint32_t PIN1               :2;
	uint32_t PIN2               :2;
	uint32_t PIN3               :2;
	uint32_t PIN4               :2;
	uint32_t PIN5               :2;
	uint32_t PIN6               :2;
	uint32_t PIN7               :2;
	uint32_t PIN8               :2;
	uint32_t PIN9               :2;
	uint32_t PIN10              :2;
	uint32_t PIN11              :2;
	uint32_t PIN12              :2;
	uint32_t PIN13              :2;
	uint32_t PIN14              :2;
	uint32_t PIN15              :2;

}GPIOx_MODER_t;


typedef struct{

	uint32_t PIN0               :1;
	uint32_t PIN1               :1;
	uint32_t PIN2               :1;
	uint32_t PIN3               :1;
	uint32_t PIN4               :1;
	uint32_t PIN5               :1;
	uint32_t PIN6               :1;
	uint32_t PIN7               :1;
	uint32_t PIN8               :1;
	uint32_t PIN9               :1;
	uint32_t PIN10              :1;
	uint32_t PIN11              :1;
	uint32_t PIN12              :1;
	uint32_t PIN13              :1;
	uint32_t PIN14              :1;
	uint32_t PIN15              :1;
	uint32_t RESERVED           :16;
}GPIOx_ODR_t;


typedef struct{

	uint32_t PIN0               :1;
	uint32_t PIN1               :1;
	uint32_t PIN2               :1;
	uint32_t PIN3               :1;
	uint32_t PIN4               :1;
	uint32_t PIN5               :1;
	uint32_t PIN6               :1;
	uint32_t PIN7               :1;
	uint32_t PIN8               :1;
	uint32_t PIN9               :1;
	uint32_t PIN10              :1;
	uint32_t PIN11              :1;
	uint32_t PIN12              :1;
	uint32_t PIN13              :1;
	uint32_t PIN14              :1;
	uint32_t PIN15              :1;
	uint32_t RESERVED           :16;
}GPIOx_IDR_t;

#endif /* GPIO_DRIVER_H_ */
