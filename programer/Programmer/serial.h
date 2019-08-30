/*
 * File: serial.h
 * Project: programmer
 *
 * Created on: 25.1.2019
 * Author: Eldad Hellerman
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <windows.h>
#include <stdio.h>

int serial_open(int com_number, int baud_rate);
int serial_close(void);
DWORD serial_write(char *buffer, int buffer_length);
DWORD serial_read(char *buffer, int buffer_length);

#endif /* SERIAL_H_ */
