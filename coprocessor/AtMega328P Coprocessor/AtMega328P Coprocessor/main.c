/*
 * Project: AtMega328P Coprocessor
 * File: AtMega328P Coprocessor.c
 *
 * Created: 16/01/2019 23:34:23
 * Author: Eldad Hellerman
 */

/* setup:
8086 -> arduino promini wiring:
	clock -> pin 5
	reset -> pin 10
*/

#include "common.h"
#include "clock_generator.h"
#include "control.h"

int main(void){
	//init_clock();
	//init_clock_250_khz();
	init_clock_500_khz();
	init_control();
	_delay_ms(250);
	
	start_clock();
	_delay_us(100);
	control_reset();
	_delay_us(100);
	while(1);
}

