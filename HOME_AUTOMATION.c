/*
 * uart.c
 *
 * Created: 2:40:43 PM
 *  Author: aditya dixit
 */ 
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#define F_CPU 12000000UL      /*It is defining frequency of our board by writing this if we use delay function it will create exact delay */

void USARTInit(uint16_t ubrr_value)     /* for uint16_t header file inttype.h is used */
{
	/*
	BAUD RATE =9600
	DATA BITS =8
	PARITY = NONE
	stop bits =1
	flow control= none
	TRANSMISSION MODE = ASYNCHRONOUS
	USART RECIEVER= ON
	USART TRANSMITTER = ON
	U2X=0
	UBRR VALUE =77
	ATMEGA 16 CALIBRATED INTERNAL RC OSCILLATOR FREQUENCY= 12MHZ
	*/
	UBRRL=ubrr_value;
	UBRRH=(ubrr_value>>8);
	UCSRC |=(1<<URSEL) | (1<<UCSZ1)|(1<<UCSZ0);
	UCSRB |=(1<<RXEN)|(1<<TXEN);
}
unsigned char USARTReadChar()
{while(!(UCSRA & (1<<RXC)));
	return UDR;
	
}
void USARTWriteChar(char data)
{while(!(UCSRA & (1<<UDRE)));
	UDR=data;
}
void main()
{ unsigned char data;
	DDRB=0xFF;
	USARTInit(77);
	while(1)
	{
		data= USARTReadChar();
		if(data=='A')
		{
			USARTWriteChar(data);
			PORTB|=0b00000001;
			_delay_ms(500);
			
		}
		else if(data=='B')
		{
			USARTWriteChar(data);
			PORTB|=0b00000010;
			_delay_ms(500);
		}
		
		else if(data=='C')
		{
			USARTWriteChar(data);
			PORTB&=0b11111101;
			_delay_ms(500);
		}
		else if(data=='D')
		{
			USARTWriteChar(data);
			PORTB&=0b11111110;
			_delay_ms(500);
		}
		
	}
}
		