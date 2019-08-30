/*
 * simpleUART.h
 *
 * Created: 05/09/2018 01:53:55
 * Author : Eldad
 */

#ifndef SIMPLEUART_H_
#define SIMPLEUART_H_

#include "stdio.h"

void init_uart_9600(void);
void init_uart_115200(void);

int uart_putchar(char c, FILE *stream);
int uart_getchar();
	
#endif /* SIMPLEUART_H_ */