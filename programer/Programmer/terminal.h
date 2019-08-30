/*
 * terminal.h
 *
 *  Created on: 6 במרץ 2019
 *      Author: Eldad
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "serial.h"
#include "cli_library_V1.h"

void terminal(int com_port, int baud_rate);

#endif /* TERMINAL_H_ */
