/*
 * File: clock_generator.c
 * Project: AtMega328P Coprocessor V2
 *
 * Created: 23.02.2019 21:30:19
 * Author: Eldad Hellerman
 */

#include "clock_generator.h"

void init_clock(){
	DDRD |= (1<<5);
	TCCR0A = 0b00100001;
	TCCR0B = 0b00001000;
	TCNT0 = 0;
	OCR0A = 4;
	//OCR0A = 2;
	TIMSK0 = 0b00000000;
	OCR0B = 1;
}

void init_clock_250_khz(){
	DDRD |= (1<<5);
	TIMSK0 = 0b00000000;
	TCNT0 = 0;
	TCCR0A = 0b00100001;
	TCCR0B = 0b00001001; //0b00001000 will stop the clock
	OCR0A = 32;
	OCR0B = 11;
}

void init_clock_500_khz(){
	DDRD |= (1<<5);
	TIMSK0 = 0b00000000;
	TCNT0 = 0;
	TCCR0A = 0b00100001;
	TCCR0B = 0b00001001; //0b00001000 will stop the clock
	OCR0A = 16;
	OCR0B = 5;
}

/*
//may be used for a dynamic clock, though a list or predefined clock values, with hard coded values is more accurate and faster.
void init_timer_clock_at(int speed_khz){
	DDRD |= (1<<5);
	TIMSK0 = 0b00000000;
	TCNT0 = 0;
	TCCR0A = 0b00100001;
	TCCR0B = 0b00001001; //0b00001000 will stop the clock
	OCR0A = 160*50/speed_khz;
	OCR0B = (160*50/speed_khz)/3;
}*/