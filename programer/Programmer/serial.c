/*
 * File: serial.c
 * Project: Programmer
 *
 * Created on: 25.1.2019
 * Author: Eldad Hellerman
 */

#include "serial.h"

static HANDLE hSerial;
static DCB dcbSerialParams = {0};
static COMMTIMEOUTS timeouts = {0};

int serial_open(int com_number, int baud_rate){
	char buffer[11];
	snprintf(buffer,11,"\\\\.\\COM%d",com_number);
	hSerial = CreateFile(buffer, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL );
	if(hSerial == INVALID_HANDLE_VALUE){
		fprintf(stderr, "Error Opening Serial Port\n");
		return(0);
	}

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if(GetCommState(hSerial, &dcbSerialParams) == 0){
		CloseHandle(hSerial);
		return(0);
	}
	dcbSerialParams.BaudRate = baud_rate;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if(SetCommState(hSerial, &dcbSerialParams) == 0){
		fprintf(stderr, "Error Setting Serial Port Parameters\n");
		CloseHandle(hSerial);
		return(0);
	}

	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutConstant = 3000;
	timeouts.ReadTotalTimeoutMultiplier = 2;
	timeouts.WriteTotalTimeoutConstant = 150;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if(SetCommTimeouts(hSerial, &timeouts) == 0){
		fprintf(stderr, "Error Setting Serial Port Timeout Parameters\n");
		CloseHandle(hSerial);
		return(0);
	}
	return 1;
}

int serial_close(){
    if(!CloseHandle(hSerial)){
        fprintf(stderr, "Error Closing Serial Port\n");
        return(0);
    }
	return(1);
}

DWORD serial_write(char *buffer, int buffer_length){
	DWORD bytes_written;
	if(!WriteFile(hSerial, buffer, buffer_length, &bytes_written, NULL)){
		fprintf(stderr, "Error Writing To Serial Port\n");
		return(0);
	}
	return(bytes_written);
}

DWORD serial_read(char *buffer, int buffer_length){
	DWORD bytes_read;
	if(!ReadFile(hSerial, buffer, buffer_length, &bytes_read, NULL)){
		fprintf(stderr, "Error Reading From Serial Port\n");
		return(0);
	}
	return(bytes_read);
}
