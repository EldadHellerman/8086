/*
 * word_main.c
 *
 * Created: 23/01/2019 00:18:32
 *  Author: Eldad
 */ 

/*
 * atmega_memory_test.c
 *
 * Created: 21/01/2019 19:22:31
 * Author : Eldad
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include "simpleUART.h"
#include "avr/interrupt.h"
#include "defines.h"

uint16_t flash_read_word(uint16_t address){
	/*steps:
		-set RD, WR, BHE, ALE off
		-set RD, WR, BHE, ALE as output
		-set AD as output
		-BHE on
		-output address
		-latch
		-BHE off
		-set AD as input
		-RD on
		-read data
		-RD off
	*/
	uint16_t result = 0;
	address <<= 1;
	AD_LOW_DDR = 0xff; AD_HIGH_DDR = 0xff;
	AD_LOW_PORT = (address & 0xff); AD_HIGH_PORT = ((address>>8) & 0xff); _delay_us(1);
	BHE_ON();
	ALE_ON(); ALE_OFF(); _delay_us(1);
	BHE_OFF();
	AD_LOW_DDR = 0; AD_HIGH_DDR = 0; /*_delay_us(100);*/ AD_LOW_PORT = 0; AD_HIGH_PORT = 0; _delay_us(1);
	RD_ON(); _delay_us(1);
	result = AD_HIGH_PIN; result <<= 8; result |= AD_LOW_PIN;
	RD_OFF();
	return(result);
}

void flash_write_word(uint16_t address, uint16_t data){
	/*steps:
		-set RD, WR, BHE, ALE off
		-set RD, WR, BHE, ALE as output
		-set AD as output
		-BHE on
		-output address
		-latch
		-BHE off
		-output data
		-WR on
		-WR off
		-set AD as input
	*/
	//printf("address %d, data %d\n", address, data);
	address <<= 1;
	AD_LOW_DDR = 0xff; AD_HIGH_DDR = 0xff;
	AD_LOW_PORT = (address & 0xff); AD_HIGH_PORT = ((address>>8) & 0xff); _delay_us(1);
	BHE_ON();
	ALE_ON(); ALE_OFF(); _delay_us(1);
	BHE_OFF();
	AD_LOW_PORT = data & 0xff; AD_HIGH_PORT = (data>>8) & 0xff; _delay_us(1);
	WR_ON(); _delay_us(1);
	WR_OFF(); _delay_us(1);
	AD_LOW_DDR = 0; AD_HIGH_DDR = 0; /*_delay_us(100);*/ AD_LOW_PORT = 0; AD_HIGH_PORT = 0; _delay_us(1);
}

int test_flash_word(void){
	int errors = 0;
	for(int b=0; b<1024*2; b++){
		for(int i=0; i<256; i++) flash_write_word(i,b);
		for(int i=0; i<256; i++) if(flash_read_word(i) != b) errors++;
	}
	//if(errors != 0) printf("after stage #1, %d errors\n",errors);
	for(int page=0; page<8; page++){
		for(int i=0; i<256; i++) flash_write_word((page<<8) + i,i);
		for(int i=0; i<256; i++) if(flash_read_word((page<<8) + i) != i) errors++;
		//if(errors != 0) printf("after stage #2, %d errors\n",errors);
		
		for(int i=0; i<256; i++) flash_write_word((page<<8) + i,~i);				//this test does not work!
		for(int i=0; i<256; i++) if(flash_read_word((page<<8) + i) != ~i) errors++;	//i don't know why..
		
		for(int i=0; i<256; i++) flash_write_word((page<<8) + i,(i + 5)%256);
		for(int i=0; i<256; i++) if(flash_read_word((page<<8) + i) != (i + 5)%256) errors++;
		
		if(errors != 0) printf("after stage #3, %d errors\n",errors);
		for(int i=0; i<256; i++) flash_write_word((page<<8) + i,0xffff);
	}
	return(errors);
}

uint8_t flash_read_byte(uint16_t address){
	/*steps:
		-set RD, WR, BHE, ALE off
		-set RD, WR, BHE, ALE as output
		-set AD as output
		-BHE on
		-output address
		-latch
		-BHE off
		-set AD as input
		-RD on
		-read data
		-RD off
	*/
	uint8_t result = 0;
	char high_byte = address & 0x01;
	AD_LOW_DDR = 0xff; AD_HIGH_DDR = 0xff;
	AD_LOW_PORT = (address & 0xff); AD_HIGH_PORT = ((address>>8) & 0xff); _delay_us(1);
	if(high_byte) BHE_ON();
	ALE_ON(); ALE_OFF(); _delay_us(1);
	if(high_byte) BHE_OFF();
	AD_LOW_DDR = 0; AD_HIGH_DDR = 0; /*_delay_us(100);*/ AD_LOW_PORT = 0; AD_HIGH_PORT = 0; _delay_us(1);
	RD_ON(); _delay_us(1);
	result = (high_byte) ? AD_HIGH_PIN : AD_LOW_PIN;
	RD_OFF();
	return(result);
}

void flash_write_byte(uint16_t address, uint8_t data){
	/*steps:
		-set RD, WR, BHE, ALE off
		-set RD, WR, BHE, ALE as output
		-set AD as output
		-BHE on
		-output address
		-latch
		-BHE off
		-output data
		-WR on
		-WR off
		-set AD as input
	*/
	//printf("address %d, data %d\n", address, data);
	char high_byte = address & 0x01;
	AD_LOW_DDR = 0xff; AD_HIGH_DDR = 0xff;
	AD_LOW_PORT = (address & 0xff); AD_HIGH_PORT = ((address>>8) & 0xff); _delay_us(1);
	if(high_byte) BHE_ON();
	ALE_ON(); ALE_OFF(); _delay_us(1);
	if(high_byte) BHE_OFF();
	if(high_byte) AD_HIGH_PORT = data; else AD_LOW_PORT = data ; _delay_us(1);
	WR_ON(); _delay_us(1);
	WR_OFF(); _delay_us(1);
	AD_LOW_DDR = 0; AD_HIGH_DDR = 0; /*_delay_us(100);*/ AD_LOW_PORT = 0; AD_HIGH_PORT = 0; _delay_us(1);
}

void hold_bus(void){
	RD_OFF(); WR_OFF(); BHE_OFF(); ALE_OFF(); //enable pull-ups
	HOLD_ON();
	while(!(CONTROL_PIN & (1<<HLDA)));
	CONTROL_DDR |= (1<<RD) | (1<<WR) | (1<<BHE) | (1<<ALE);
}

void release_bus(void){
	CONTROL_DDR &= ~((1<<RD) | (1<<WR) | (1<<BHE) | (1<<ALE));
	HOLD_OFF();
	while(CONTROL_PIN & (1<<HLDA));
	RD_ON(); WR_ON(); BHE_ON(); ALE_OFF(); //remove all pull-ups
}

void print_memory_bytes(void){
	for(unsigned int i=0; i<1024*4; i++){
		uint8_t d = flash_read_byte(i);
		if((i%16) == 0) printf("%03X:    ",i);
		printf("%02X,",d);
		if((i%16) == 15) printf("\n");
	}
}

void reset_cycle(void){
	RESET_ON();
	_delay_ms(10);
	RESET_OFF();
}

uint32_t get_uint32(void){
	uint32_t data = 0;
	for(char i=0; i<4; i++){
		data <<= 8;
		data |= uart_getchar();
	}
	return(data);
}

void dump_memory(){
	uint32_t start_address = get_uint32();
	uint32_t length = get_uint32();
	for(int i=start_address; i<start_address+length; i++) uart_putchar(flash_read_byte((uint16_t)i),NULL);
}

void upload_to_memory(void){
	uint32_t start_address = get_uint32();
	uint32_t length = get_uint32();
	for(int i=start_address; i<start_address+length; i++) flash_write_byte((uint16_t)i,uart_getchar());
}

void generate_interrupt(void){
	unsigned char number = uart_getchar();
	/*INTR_ON();
	_delay_ms(1);
	INTR_OFF();
	return;*/
	INTR_ON();
	while(CONTROL2_PIN & (1<<INTA));
	INTR_OFF();
	while(!(CONTROL2_PIN & (1<<INTA)));
	while(CONTROL2_PIN & (1<<INTA));
	AD_LOW_DDR = 0xff;
	AD_LOW_PORT = number;
	while(!(CONTROL2_PIN & (1<<INTA)));
	AD_LOW_DDR = 0; AD_LOW_PORT = 0;
}

void debug_to_uart(void){
	uint16_t address = 0, data;
	_Bool read = 0;
	while(!(CONTROL_PIN & (1<<ALE))){
		 address = AD_HIGH_PIN;
		 address <<= 8;
		 address |= AD_LOW_PIN;
	}
	while((CONTROL_PIN & (1<<RD)) && (CONTROL_PIN & (1<<WR)));
	read = !(CONTROL_PIN & (1<<RD));
	data = AD_HIGH_PIN;
	data <<= 8;
	data |= AD_LOW_PIN;
	hold_bus();
	if(read) printf("read from "); else printf("write to ");
	printf("address %.2X data %.2X\n",address,data);
	release_bus();
}

//first instruction runs from word address 240 (as it should be).
//TODO debugging using 8086 TF flag! interrupts after every instruction!

volatile _Bool debug_on = 0;

int main(void){
	init_uart_9600(); //init_uart_115200(); //115200 has inaccuracy issues
	CONTROL_DDR |= (1<<HOLD);
	CONTROL_DDR &= ~(1<<HLDA);
	CONTROL_DDR |= (1<<RST);
	CONTROL2_PORT &= ~((1<<INTR) | (1<<INTA));
	CONTROL2_DDR |= (1<<INTR);
	RESET_ON();
	_delay_ms(10);
	RESET_OFF();
	sei();
	
	while(1){
		if(debug_on) debug_to_uart();
	}
}

ISR(USART0_RX_vect){
	switch(UDR0){
		case 'c':
			release_bus();
			break;
		case 'p':
			hold_bus();
			break;
		case 'r':
			reset_cycle();
			hold_bus();
			break;
		case 'm':
			dump_memory();
			break;
		case 'u':
			upload_to_memory();
			break;
		case 'i':
			generate_interrupt();
			break;
		case 'd':
			debug_on = !debug_on;
			break;
	}
}


/*
p - pause - hold bus
c - continue - release bus
r - reset (will also hold bus and wait for a start)

m - read memory
u $length $program - upload program

status (reporting reads and writes to computer):
ss - status start
sp - status pause

clock:

cs - clock start
cp - clock pause
cc $freq - clock change to new frequency



TODO:
	debugging:
		features to enables following a certain memory location?
		features to get data on what the processor is doing (r/w, status lines, etc)
	make debugger read and write faster from/to memory as well as com port
	
	make a make file that assembles the program and uploads it via the cmd utility
*/