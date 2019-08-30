/*
 * simpleUART.c
 *
 * Created: 05/09/2018 01:53:55
 * Author : Eldad
 */

#include "simpleUART.h"

#include "avr/common.h" //for SREG definition
#include "avr/interrupt.h"

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_WRITE);

#define F_CPU 16000000UL

/*#ifndef F_CPU
	#define F_CPU 16000000UL
	#warning "F_CPU undefined. using default 16000000"
#endif*/

#ifndef BAUD_TOL
	#define BAUD_TOL 2
#endif

//#define BAUD 9600
//#define BAUD 57600
#define BAUD 230400
#include <util/setbaud.h>

void init_uart_9600(){
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#endif
	//UCSR0B = (1<<TXEN0) | (1<<UDRIE0) | (1<<RXEN0) | (1<<RXCIE0);
	UCSR0B = (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0); //UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	stdout = &uart_stdout;
}

#undef BAUD
#define BAUD 115200
#include <util/setbaud.h>

void init_uart_115200(){
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#endif
	//UCSR0B = (1<<TXEN0) | (1<<UDRIE0) | (1<<RXEN0) | (1<<RXCIE0);
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	stdout = &uart_stdout;
}

int uart_putchar(char c, FILE *stream){
	//if(c == '\n') uart_putchar('\r',stream);
	unsigned char sreg = SREG;
	cli();
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = c;
	SREG = sreg;
	return(0);
}

int uart_getchar(){
	while(!(UCSR0A & (1<<RXC0)));
	return((int)UDR0);
}