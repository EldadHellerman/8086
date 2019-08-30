/*
 * File: spi.c
 * Project: AtMega328P Coprocessor V2
 *
 * Created: 01.03.2019 16:00:57
 * Author: Eldad Hellerman
 */

#include "spi.h"

void init_spi(void){
	SET_HIGH(SHREG_OE); SET_OUTPUT(SHREG_OE);
	SET_HIGH(SHREG_LD); SET_OUTPUT(SHREG_LD);
	SET_LOW(SHREG_RCLK); SET_OUTPUT(SHREG_RCLK); //
	SET_OUTPUT(SPI_MOSI); SET_OUTPUT(SPI_SCK);  //spi_ss is SHREG_RCLK
	SPCR = (1<<SPE) | (1<<MSTR); //CPOL is changed when reading data
	SPSR |= (1<<SPI2X);
}

uint16_t spi(uint16_t data){
	uint16_t result;
	SPDR = data>>8;
	while(!(SPSR & 0x80));
	result = SPDR;
	SPDR = data & 0xff;
	result <<= 8;
	while(!(SPSR & 0x80));
	result |= SPDR;
	return(result);
}

uint16_t spi_recieve(){
	uint16_t result;
	SPDR = 0;
	while(!(SPSR & 0x80));
	result = SPDR;
	SPDR = 0;
	result <<= 8;
	while(!(SPSR & 0x80));
	result |= SPDR;
	return(result);
}

void spi_send(uint32_t data){
	SPDR = (data>>16) & 0xff;
	while(!(SPSR & (1<<SPIF)));
	SPDR = (data>>8) & 0xff;
	while(!(SPSR & (1<<SPIF)));
	SPDR = (data>>0) & 0xff;
	while(!(SPSR & (1<<SPIF)));
}
