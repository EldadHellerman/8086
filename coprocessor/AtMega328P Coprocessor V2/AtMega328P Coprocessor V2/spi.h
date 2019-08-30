/*
 * File: spi.h
 * Project: AtMega328P Coprocessor V2
 *
 * Created: 01.03.2019 16:02:46
 * Author: Eldad Hellerman
 */

#ifndef SPI_H_
#define SPI_H_

#include "common.h"

void init_spi(void);
uint16_t spi(uint16_t data);
uint16_t spi_recieve();
void spi_send(uint32_t data);

#endif /* SPI_H_ */