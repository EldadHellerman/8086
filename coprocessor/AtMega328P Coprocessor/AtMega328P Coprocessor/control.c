/*
 * Project: AtMega328P Coprocessor
 * File: control.c
 *
 * Created: 21/01/2019 16:29:05
 * Author: Eldad Hellerman
 */

#include "control.h"

void init_control(){
	RST_HIGH();
	DDRB = 0x04;
}

void control_reset(){
	RST_HIGH();
	_delay_us(20);
	RST_LOW();
}