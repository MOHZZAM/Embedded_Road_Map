/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "gpio_driver.h"


int main(void)
{
	RCC_AHB1ENR_t volatile *const gpio_clock = (RCC_AHB1ENR_t *)gpio_port_b_clock_enable;
	GPIOx_MODER_t volatile *const gpio_mode = (GPIOx_MODER_t *)gpio_port_b_mode_register;
	GPIOx_ODR_t   volatile *const gpio_data = (GPIOx_ODR_t *)gpio_port_b_output_register;

	gpio_clock->GPIOBEN = 1;
	gpio_mode->PIN0 = 1;
	gpio_mode->PIN7 = 1;
	gpio_mode->PIN14 = 1;
	gpio_data->PIN0 = 1;

	while (1)
	{
		gpio_data->PIN0 = 1;
		gpio_data->PIN7 = 0;
		gpio_data->PIN14 = 1;
		for (uint32_t i = 0; i < 100000 ; i++);
		gpio_data->PIN0 = 0;
		gpio_data->PIN7 = 1;
		gpio_data->PIN14 = 0;
		for (uint32_t i = 0; i < 100000 ; i++);
	}

    /* Loop forever */
	for(;;);
}