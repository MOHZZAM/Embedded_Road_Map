#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_DRIVER.h"

void motor(unsigned char , unsigned char*);

int main()
{
	lcd_init();
	while(1)
	{
		motor(70,"forward");
		_delay_ms(10000);
		motor(100,"reverse");
		_delay_ms(10000);
		motor(0,"stop");
		_delay_ms(10000);
	}
}

void motor(unsigned char speed , unsigned char cmnd[10])
{
	DDRD |= (1<<PIND5)|(1<<PIND4); //PB4 = OCR1B , PB5 = OCR1A
	
	if(cmnd == "forward")
	{
		OCR1AH = 0;
		OCR1AL = (2.55 * speed); //setting pwm width
		TCCR1A |= (1<<COM1A1)|(1<<WGM10); //pb5 as non inverted mode
		TCCR1B |= (1<<WGM12)|(1<<CS10); //mode = 5 ,no prescaler
		TCCR1A &= ~((1<<COM1B0)|(1<<COM1B1)); //pb4 as normal output
		PORTB &= ~(1<<PINB4); //set pb4 low 
	}
	if(cmnd == "reverse")
	{
		OCR1BH = 0;
		OCR1BL = (2.55 * speed); //setting pwm width
		TCCR1A |= (1<<COM1B1)|(1<<WGM10); //pb4 non inverted mode
		TCCR1B |= (1<<WGM12)|(1<<CS10); //mode 5 , no pre scaler 
		TCCR1A &= ~((1<<COM1A0)|(1<<COM1A1)); //pb5 normal output
		PORTB &= ~(1<<PINB5); //set pb5 low
	}
	if(cmnd == "stop")
	{
		TCCR1A &= ~((1<<COM1B0)|(1<<COM1B1)|(1<<COM1A0)|(1<<COM1A1)); //setting normal output of pb4 and pb5
		PORTD &= ~((1<<PINB4)|(1<<PINB5)); //set pb4 and pb5 low
	}
}