/*
 * File: clock_generator.h
 * Project: AtMega328P Coprocessor V2
 *
 * Created: 23.02.2019 21:28:58
 * Author: Eldad Hellerman
 */

#ifndef CLOCK_GENERATOR_H_
#define CLOCK_GENERATOR_H_

#include "common.h"

#define start_clock()	TCCR0B &= ~0x07; TCCR0B |= 0x01
#define stop_clock()	TCCR0B &= ~0x07

void init_clock(void);
void init_clock_250_khz(void);
void init_clock_500_khz(void);

#endif /* CLOCK_GENERATOR_H_ */