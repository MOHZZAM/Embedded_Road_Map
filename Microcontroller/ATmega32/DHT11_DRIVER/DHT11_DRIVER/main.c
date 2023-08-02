#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD_DRIVER.h"

#define dht_port PINC
#define dht_DDR DDRC
#define dht_pin PINC2
uint8_t I_RH , D_RH , I_Temp , D_Temp , check_sum_byte , c=0 , data1[5];

void dht_request(void);
void dht_response(void);
uint8_t dht_data();
void dht_humidity(void);
void dht_temperature(void);

int main()
{
	lcd_init();
	while(1)
	{
		lcd_gotoxy(1,1);
		dht_humidity();
		lcd_gotoxy(2,1);
		dht_temperature();	
	}
}

void dht_request()
{
	dht_DDR |= (1<<dht_pin); //set pin as output
	PORTC &= ~(1<<dht_pin); //giving delay of 18ms
	_delay_ms(20);
	PORTC |= (1<<dht_pin); //pull up register
}

void dht_response(void)
{
	dht_DDR &= ~(1<<dht_pin); //making pin input
	while((1<<dht_pin) & dht_port); //go if pin low
	while((1<<dht_pin & dht_port) == 0); //go if pin high
	while((1<<dht_pin) & dht_port); //go if pin low
}

uint8_t dht_data()
{
	for(int q=0;q<8;q++)
	{
		while((dht_port & (1<<dht_pin))==0); //go if pin high
		_delay_us(30);
		if((dht_port & (1<<dht_pin))!=0) //go if pin high
		{
			c = (c<<1)|(0x01);
		}
		else
		c = c<<1;
		while(dht_port & (1<<dht_pin)); //go if pin low
	}
	return c;
}

void dht_humidity(void)
{
    dht_request();
    dht_response();
    I_RH = dht_data();
    D_RH = dht_data();
    I_Temp = dht_data();
    D_Temp = dht_data();
	check_sum_byte = dht_data();
	if((I_RH + D_RH + I_Temp + D_Temp) != check_sum_byte)
	{
		lcd_print("Error");
	}
	else
	{
		itoa(I_RH , data1 , 10);
		lcd_print(data1);
		lcd_print(".");
		itoa(D_RH , data1 , 10);
		lcd_print(data1);
	}
	_delay_ms(1000);
}

void dht_temperature(void)
{
	dht_request();
	dht_response();
	I_RH = dht_data();
	D_RH = dht_data();
	I_Temp = dht_data();
	D_Temp = dht_data();
	check_sum_byte = dht_data();
	if((I_RH + D_RH + I_Temp + D_Temp) != check_sum_byte)
	{
		lcd_print("Error");
	}
	else
	{
		itoa(I_Temp , data1 , 10);
		lcd_print(data1);
		lcd_print(".");
		itoa(D_Temp , data1 , 10);
		lcd_print(data1);
	}
	_delay_ms(1000);
}

