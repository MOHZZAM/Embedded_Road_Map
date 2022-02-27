#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_DRIVER.h"

void steper_motor(unsigned int , unsigned char*);

#define steper_motor_port PORTB
#define steper_motor_DDR DDRB

int main()
{
	lcd_init();
	while(1)
	{
		steper_motor(90 , "right");
		lcd_gotoxy(1,1);
		lcd_print("right");
		_delay_ms(3000);
		steper_motor(90 , "left");
		lcd_gotoxy(1,1);
		lcd_print("left");
		_delay_ms(3000);
	}
	return 0;
}

void steper_motor(unsigned int angle , unsigned char direction[10])
{
	unsigned int degree = ((angle * 5.66)/4);
    steper_motor_DDR |= 0x0f;
	if(direction == "right")
	{
		for(unsigned int i=0;i<degree;i++)
		{
			steper_motor_port = 0x01;
			_delay_ms(3);
			steper_motor_port = 0x02;
			_delay_ms(3);
			steper_motor_port = 0x04;
			_delay_ms(3);
			steper_motor_port = 0x08;
			
		}
	}
	if(direction == "left")
	{
		for(unsigned int i=0;i<degree;i++)
		{
			steper_motor_port = 0x08;
			_delay_ms(3);
			steper_motor_port = 0x04;
			_delay_ms(3);
			steper_motor_port = 0x02;
			_delay_ms(3);
			steper_motor_port = 0x01;
			
		}
	}
}



