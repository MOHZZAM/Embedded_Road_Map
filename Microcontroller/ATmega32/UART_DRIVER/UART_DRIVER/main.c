/*
 * UART_DRIVER.c
 *
 * Created: 20-02-2022 06:00:28
 * Author : MD MOHZZAM
 */ 

// define cpu speed 16MHZ
#define F_CPU 16000000UL
// including avr input output header file
#include <avr/io.h>
// include avr interrupt header file
#include <avr/interrupt.h>
//delay
#include <util/delay.h>

//UART receiver transmitter
unsigned char receiver , transmitter;

// UART Intilization code
void uart_init()
{
	UBRRL = 0x67; //Baud rate is 9600bps and frequency is 16MHz
	UCSRB = (1<<TXEN)|(1<<RXEN)|(1<<RXCIE); //transmitter,receiver,receiver interrupt and UDR interrupt enable
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	sei();
}


// UART receiver interrupt
ISR (USART_RXC_vect)
{
	unsigned char data;
	data = UDR;
	uart_print(data);
	
	
}

// UART Transmitter
unsigned char uart_transmitter(unsigned char data )
{
	UDR = data;
	_delay_ms(1000);
	UCSRA = (1<<UDRE);
}

void uart_print(unsigned char ch[100])
{
	for(unsigned char i=0;i<100;i++)
	{
		uart_transmitter(ch[i]);
		if(ch[i] == 0)
		{
			ch[100] = { };
			break;
		}
		
	}
}

int main(void)
{
   unsigned char data;
   uart_init();
   uart_print("or kya haal hai");
   
    while (1) 
    {
		
    }
}

