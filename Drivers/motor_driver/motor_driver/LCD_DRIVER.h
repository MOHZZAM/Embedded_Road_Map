/*
 * LCD_DRIVER.h
 *
 * Created: 23-02-2022 06:07:37
 *  Author: moazz
 */ 


#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#define lcd_port PORTC
#define lcd_DDR DDRC
#define lcd_RS 0
#define lcd_EN 1

void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_init(void);
void lcd_gotoxy(unsigned char , unsigned char);
void lcd_print(unsigned char*);
void lcd_clear(void);



void lcd_command(unsigned char cmnd)
{
	lcd_port = ((lcd_port & 0x0f)|(cmnd & 0xf0));
	lcd_port &= ~(1<<lcd_RS);
	lcd_port |= (1<<lcd_EN);
	_delay_us(1);
	lcd_port &= ~(1<<lcd_EN);
	_delay_us(100);
	
	lcd_port = ((lcd_port & 0x0f)|(cmnd << 4));
	lcd_port |= (1<<lcd_EN);
	_delay_us(1);
	lcd_port &= ~(1<<lcd_EN);
	_delay_us(100);
}

void lcd_data(unsigned char data)
{
	lcd_port = ((lcd_port & 0x0f)|(data & 0xf0));
	lcd_port |= (1<<lcd_RS);
	lcd_port |= (1<<lcd_EN);
	_delay_us(1);
	lcd_port &= ~(1<<lcd_EN);
	_delay_us(100);
	
	lcd_port = ((lcd_port & 0x0f)|(data << 4));
	lcd_port |= (1<<lcd_EN);
	_delay_us(1);
	lcd_port &= ~(1<<lcd_EN);
	_delay_us(100);
}

void lcd_init(void)
{
	lcd_DDR = 0xff;
	
	lcd_command(0x33); //delay for lcd
	lcd_command(0x32); //delay for lcd
	lcd_command(0x28); //set 4bit mode , number of lines 2 and 5x7 dots representation
	lcd_command(0x0c); //set lcd on and cursor on
	lcd_command(0x01); //clear lcd
	_delay_us(2000);
	lcd_command(0x06); //shift cursor right
}

void lcd_gotoxy(unsigned char x , unsigned char y)
{
	unsigned char First_addr[] = { 0x80 , 0xc0 , 0x94 , 0xd4 };
	lcd_command(First_addr[x-1] + y-1);
	_delay_us(100);
}

void lcd_print(unsigned char *str)
{
	unsigned char i;
	for(i=0;str[i] != 0;i++)
	{
		lcd_data(str[i]);
	}
}

void lcd_clear(void)
{
	lcd_command(0x01);
}





#endif /* LCD_DRIVER_H_ */