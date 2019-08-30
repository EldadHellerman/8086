/*
 * File: simpleUART.c
 * Project: AtMega328P Coprocessor V2
 *
 * Created: 05.09.2018 01:53:55
 * Author: Eldad Hellerman
 */

#include "simpleUART.h"

#include "common.h"
#include "avr/common.h" //for SREG definition
#include "avr/interrupt.h"

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_WRITE);

void init_uart_115200(){
	//200K - 4 | (9 & U2X)  ,  400K - (4 & U2X)  ,  500K - 1 | (3 & U2X)  ,  1M doesn't work (because of usb-to-uart converter)
	UBRR0 = 4;
	UCSR0A |= (1 << U2X0);
	//UCSR0B = (1<<TXEN0) | (1<<UDRIE0) | (1<<RXEN0) | (1<<RXCIE0);
	UCSR0B = (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	stdout = &uart_stdout;
}

int uart_putchar(char c, FILE *stream){
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