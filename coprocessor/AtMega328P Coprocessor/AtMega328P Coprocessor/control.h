/*
 * Project: AtMega328P Coprocessor
 * File: control.h
 *
 * Created: 21/01/2019 16:26:08
 * Author: Eldad Hellerman
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "common.h"

#define RST_HIGH() PORTB |= 0x04
#define RST_LOW() PORTB &= ~0x04


void init_control(void);
void control_reset(void);

#endif /* CONTROL_H_ */