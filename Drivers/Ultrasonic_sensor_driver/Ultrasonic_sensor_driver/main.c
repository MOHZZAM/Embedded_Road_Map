#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_DRIVER.h"

unsigned char ultrasonic_sensor(void);

int main()
{
	lcd_init();
	unsigned int value , temp,data[10];
	temp = 0x1f; //write lower value
	value = 0x02; //write high value
	value = (value<<8)|(temp);//number of clocks
	itoa(value,data,10);
	lcd_gotoxy(1,1);
	lcd_print(data);
	value = (value * 64)/2; //time taken
	value = 0.034 * value; //distance calculation
	itoa(value,data,10);
	lcd_gotoxy(2,1);
	lcd_print(data);
	while(1);
	
}

unsigned char ultrasonic_sensor(void)
{
	unsigned int value , temp;
	DDRC |= (1<<PINC3);
	PORTC |= (1<<PINC3); //high pulse
	PORTC &= ~(1<<PINC3); //low pulse
	_delay_us(15); //triggering ultrasonic sensor
	PORTC |= (1<<PINC3); //high pulse
	
	PORTD |= (1<<PIND6);
	TCCR1A = 0; //normal mode
	TCCR1B |= (1<<CS10)|(1<<CS12); // clk/1024 and falling edge
	while(((1<<ICF1) & (TIFR) ) == 0);
	TIFR = (1<<ICF1);
	temp = ICR1L; //write lower value
	value = ICR1H; //write high value
	value = (value<<8)|(temp);//number of clocks
	value = (value * 64)/2; //time taken
	value = 0.034 * value; //distance calculation
	return value;
}