/*
 * Project: AtMega328P Coprocessor
 * File: clock_generator.c
 *
 * Created: 21/01/2019 16:09:58
 * Author: Eldad Hellerman
 */

#include "clock_generator.h"

#define CLK_HIGH() PORTB |= 0x10
#define CLK_LOW() PORTB &= ~0x10
#define NOP() asm("NOP\r\n")

void init_clock(){
	DDRD |= (1<<5);
	TCCR0A = 0b00100001;
	TCCR0B = 0b00001000;
	TCNT0 = 0;
	OCR0A = 4;
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

/*
void clock_2_mhz(void){
	cli();
	while(1){
		CLK_HIGH();
		NOP();
		CLK_LOW();
		NOP();
	}
}

void clock_500_khz(void){
	cli();
	while(1){
		CLK_HIGH();
		NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
		CLK_LOW();
		NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
		NOP(); NOP(); NOP(); NOP(); NOP(); NOP();
		NOP(); NOP(); NOP(); NOP(); NOP();
	}
}
*/