/*
 * File main.c
 * Project: AtMega328P Coprocessor V2
 *
 * Created: 5.2.2019 19:08:20
 * Author: Eldad Hellerman
 */

/* TODO:
-program as follows:
	read 256 or as much as left into a buffer
	(send checksum of 256 bytes, and wait for ACK from computer, or NACK if it should be aborted)
	program them into memory
	send ACK back to computer, so he can send another 256 bytes or whatever is left

-dump memory as follows:
	write 256 or as much as left into a buffer (while calculating checksum)
	send 256 bytes or as much as left
	(send checksum)
	wait for ACK to continue or NACK to abort
	
-switch from phase correct pwm to fast pwm
-can SREG_RCLK be connected to SCK?
-i think that shreg_rclk and shreg_ld can be connected to the same pin. (to spi ss which is shreg_rclk will make more sense).

Troubleshooting tips:
	check connections from ic to pads - A14 and A16 of the flash IC were open between the pad and the chip itself (on the PCB)
	
Data:
8086 interrupt types are:
 0 - divided by 0
 1 - if TF (trap flag) is set - single step execution
 2 - NMI
 3 - INT3, meant for calling the debugger
 4 - INTO (interrupt if OF flag is set)
 
internal interrupts ("INT 123" for example) cannot be turned off.
interrupts 0-31 are supposedly 'reserved'
*/

#include "common.h"
#include "clock_generator.h"
#include "spi.h"
#include "simpleUART.h"
#include <stdio.h>
#include <avr/interrupt.h>

char buffer[256];

void ad_set(uint32_t address){
	spi_send(address);
	RCLK_PULSE();
}

uint16_t ad_get(void){
	SPCR |= (1<<CPOL); //this change of CPOL is required in order to get valid data
	LD_PULSE(); //doesnt work if LD_PULSE is before previous line, why?
	uint16_t r = spi_recieve();
	SPCR &= ~(1<<CPOL);
	return(r);
}

void hold_bus(void){
	SET_INPUT_LOW(ALE);
	SET_INPUT_HIGH(RD);
	SET_INPUT_HIGH(WR);
	HOLD_ON();
	while(!GET_INPUT(HLDA));
	SET_OUTPUT(ALE);
	SET_OUTPUT(RD);
	SET_OUTPUT(WR);
}

void release_bus(void){
	SET_LOW(ALE); SET_INPUT(ALE);
	SET_HIGH(RD); SET_INPUT(RD);
	SET_HIGH(WR); SET_INPUT(WR);
	HOLD_OFF();
	while(GET_INPUT(HLDA));
	SET_LOW(RD);
	SET_LOW(WR);
}

void reset_cycle(void){
	SET_HIGH(RESET);
	_delay_us(20);
	SET_LOW(RESET);
}

uint16_t read_word(uint32_t address){
	address &= ~1;						////////////////////////////////////////TODO REMOVE
	uint16_t result;
	ad_set(address & (~BHE_IN_ADDRESS)); //make sure that BHE is 0
	//_delay_us(1);
	OE_ON();
	ALE_PULSE();
	OE_OFF();
	RD_ON();
	result = ad_get();
	RD_OFF();
	return(result);
}

uint8_t read_byte(uint32_t address){
	//ad_set(0); ////////////////////////////////////////////////////////////TODO REMOVE
	uint16_t word = read_word(address);
	return((address & 1) ? (word>>8) : (word&0xff)); //XXX XXX XXX/////////////////////////////////////////////////////is this working?
}

void write_word(uint32_t address, uint16_t data){
	address &= ~1;						////////////////////////////////////////TODO REMOVE
	ad_set(address & (~BHE_IN_ADDRESS)); //make sure that BHE is 0
	OE_ON();
	ALE_PULSE();
	ad_set(0x00000000 | data);
	WR_ON();
	WR_OFF();
	OE_OFF();
}

void write_byte(uint32_t address, uint8_t data){
	uint16_t word = read_word(address&(~1));
	if(address & 1) word = (word & 0x00ff) | (((uint16_t)data)<<8);
	else word = (word & 0xff00) | data;
	write_word(address&(~1),word);
}

void flash_read_mode(void){
	//flash_read_status_register();
	//flash_clear_status_register();
	write_word(0x80000,0x00ff);
}

uint8_t flash_read_status_register(void){
	write_word(0x80000,0x0070);
	return(read_word(0x80000) & 0xff);
}

void flash_clear_status_register(void){
	write_word(0x80000,0x0050);
}

void flash_block_erase(uint32_t block_word_address){
	write_word(0x80000 | (block_word_address<<1), 0x0020);
	write_word(0x80000 | (block_word_address<<1), 0x00D0);
	uint8_t status;
	while(1){
		//status = (read_word(0x80000) & 0xff); 
		status = flash_read_status_register();
		if(status & (1<<7)) break;
	}
	if(status & (1<<3)) printf("Vpp error\n");
	if((status & (1<<4)) && (status & (1<<5))) printf("CSE error\n");
	if(status & (1<<5)) printf("BLE error\n");
	write_word(0x80000,0x00ff);
}

void flash_write_word(uint32_t address, uint16_t data){
	write_word(address, 0x0040);
	write_word(address, data);
}

void flash_prog(uint32_t address, uint16_t data){
	flash_write_word(0x80000 | address, data);
	uint8_t status;
	while(1){
		status = flash_read_status_register();
		if(status & (1<<7)) break;
	}
	if(status & (1<<3)) printf("Vpp error\n");
	if(status & (1<<4)) printf("prg error\n");
}

void setup_c4_interrupt(void){
	SET_INPUT_HIGH(TEST); //Test is C.4, pullup to prevent accidental interrupts when wire is disconnected (wont be necessary after soldering).
	PCMSK1 = (1<<4); //PCINT12 - C.4
	PCICR = (1<<PCIE1);
}

ISR(PCINT1_vect){
	return;
	if(GET_INPUT(TEST)) return; //exit if test isn't low
	uint16_t address, data;
	SET_LOW(READY);
	address = ad_get();
	int t = 0;
	while(t<100){
		if(!GET_INPUT(WR)){ //write
			//address is not valid!. maybe if i hand insert the LD pulse before any (automatically generated) prologue code
			data = ad_get();
			//printf("wr %x\n", data);
			SET_HIGH(READY);
			break;
		}else if(!GET_INPUT(RD)){ //read
			char *str = "this is a test string message!";
			//can take as much time as i want to...
			if(address >= 30) ad_set(0);
			else ad_set((str[(address & ~1)+1] << 8) | str[(address & ~1)]);
			OE_ON();
			SET_HIGH(READY);
			while(!GET_INPUT(RD));
			OE_OFF();
			break;
		}
		t++;
	}
}

int main(void){
	SET_OUTPUT_HIGH(RESET);
	init_uart_115200(); //real baud rate is in simpleuart.h
	init_spi();
	setup_c4_interrupt();
	SET_OUTPUT(HOLD); SET_INPUT_LOW(HLDA);
	SET_OUTPUT_LOW(INTR); SET_OUTPUT_LOW(NMI); SET_INPUT(INTA);
	SET_OUTPUT_HIGH(READY);// SET_OUTPUT_LOW(TEST);
	/*init_clock_500_khz(); //*/init_clock();
	start_clock(); 
	_delay_us(100);
	
	//_delay_ms(1500);
	reset_cycle();
	hold_bus();
	
	sei();
	while(1);
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
	uint32_t address = get_uint32();
	uint32_t end_address = address + get_uint32();
	while(address < end_address){
		uint16_t word = read_word(address);
		uart_putchar(word&0xff,NULL);
		uart_putchar(word>>8,NULL);
		address += 2;
	}
	/*uint32_t start_address = get_uint32();
	uint32_t length = get_uint32();
	//printf("%04X%04X %04X%04X\n",(uint16_t)(start_address>>16),(uint16_t)(start_address&0xffff),(uint16_t)(length>>16),(uint16_t)(length&0xffff));
	//for(uint32_t i=start_address; i<start_address+length; i++){
	//	printf("%c",read_byte(i));
	//	uart_putchar(read_byte(i),NULL);
	//	//_delay_us(20);
	//}
	for(uint32_t i=start_address; i<start_address+length-1; i+=2){
		uint16_t word = read_word(i);
		 uart_putchar(word&0xff,NULL);
		 uart_putchar(word>>8,NULL);
	}*/
	//printf("done\n");
}

void upload_to_memory_old(void){
	uint32_t start_address = get_uint32();
	uint32_t length = get_uint32();
	for(uint32_t i=start_address; i<start_address+length; i+=2){
		 //write_byte(i,uart_getchar());
		 char first = uart_getchar();
		 char second = uart_getchar();
		 if(i & 0x80000) flash_prog(i,(second<<8) | first); else write_word(i,(second<<8) | first);
	}
	//printf("done\n");
}

void upload_to_memory(void){
	uint32_t start_address = get_uint32();
	uint32_t length = get_uint32() & ~1;
	uint32_t end = start_address+length;
	int buffer_pointer;
	/*
	for(uint32_t i=start_address; i< start_address + (length&0xff00); i+=256){
		//program in 256 blocks
	}
	for(uint32_t i=start_address + (length&0xff00); i< start_address + length; i+=256){
		//program whats left
	}
	*/
	for(uint32_t i=start_address; i<end; i+=256){
		_Bool flag = length < 256;
		buffer_pointer = 0;
		if(flag){ do buffer[buffer_pointer++] = uart_getchar(); while(buffer_pointer != length);}
		else{ do buffer[buffer_pointer++] = uart_getchar(); while(buffer_pointer != 256);}
		buffer_pointer = 0;
		if(flag){
			do{
				uint16_t word = buffer[buffer_pointer] | (buffer[buffer_pointer+1]<<8);
				//printf("writing %04X to %04X%04X",word,(uint16_t)((i+buffer_pointer)>>16),(uint16_t)(i+buffer_pointer));
				if(i & 0x80000) flash_prog(i+buffer_pointer,word); else write_word(i+buffer_pointer,word);
				buffer_pointer += 2;
			}while(buffer_pointer != length);
		}else{
			do{
				uint16_t word = buffer[buffer_pointer] | (buffer[buffer_pointer+1]<<8);
				if(i & 0x80000) flash_prog(i+buffer_pointer,word); else write_word(i+buffer_pointer,word);
				buffer_pointer += 2;
			}while(buffer_pointer != 256);
		}
		length -= 256;
		uart_putchar(6,NULL);
	}
	write_word(0x80000,0x00ff);
}

void generate_interrupt(void){
	SET_OUTPUT_LOW(INTR); //needed for some reason... shouldn't be as its already called in main... XXX
	SET_INPUT_LOW(INTA);
	unsigned char number = uart_getchar();
	ad_set(0x00000000 | number);
	INTR_ON();
	while(GET_INPUT(INTA));
	INTR_OFF();
	while(!GET_INPUT(INTA));
	//OE_ON();
	while(GET_INPUT(INTA));
	OE_ON(); //try moving this b4 previous while
	while(!GET_INPUT(INTA));
	OE_OFF();
}

void generate_nm_interrupt(void){
	SET_OUTPUT_LOW(NMI); //needed for some reason... shouldn't be as its already called in main... XXX
	NMI_ON();
	while(GET_INPUT(CLK));
	while(!GET_INPUT(CLK)); while(GET_INPUT(CLK)); //NMI should be on for at
	while(!GET_INPUT(CLK)); while(GET_INPUT(CLK)); //least two clock cycles
	NMI_OFF();
}

void program_my_program(void){
	flash_prog(0xffff0, 0x00BC); flash_prog(0xffff2, 0xEA10); flash_prog(0xffff4, 0x0020); flash_prog(0xffff6, 0x0000);
	flash_prog(0xffff8, 0x9090); flash_prog(0xffffa, 0x9090); flash_prog(0xffffc, 0x9090); flash_prog(0xffffe, 0x9090);
	write_word(0x80000,0x00ff);
}

void erase_flash(void){
	uint32_t address = get_uint32();
	if(!(address & 0x80000)) return;
	address = (address & ~0x80000) >> 1;
	flash_block_erase(address);
}

uint16_t address_within_flash;

ISR(USART_RX_vect){
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
		case 'n':
			generate_nm_interrupt();
			break;
		case 'd':
			//debug_on = !debug_on;
			break;
		case 'e':
			erase_flash();
			break;
		case '1':
			flash_block_erase(0x3E000);
			flash_read_mode();
			printf("done 1!\n");
			program_my_program();
			printf("done 2!\n");
			break;
		case '2':
			flash_block_erase(0x00000);
			flash_block_erase(0x10000);
			flash_block_erase(0x20000);
			flash_block_erase(0x30000);
			flash_block_erase(0x3C000);
			flash_block_erase(0x3D000);
			flash_block_erase(0x3E000);
			break;
		case '3':
			release_bus();
			_delay_ms(1000);
			hold_bus();
	}
}




/*
uint16_t Fletcher16( uint8_t *data, int count )
{
	uint16_t sum1 = 0;
	uint16_t sum2 = 0;
	int index;

	for( index = 0; index < count; ++index )
	{
		sum1 = (sum1 + data[index]) % 255;
		sum2 = (sum2 + sum1) % 255;
	}

	return (sum2 << 8) | sum1;
}


check bytes:

uint16_t csum;
uint8_t c0,c1,f0,f1;

csum = Fletcher16( data, length);
f0 = csum & 0xff;
f1 = (csum >> 8) & 0xff;
c0 = 0xff - (( f0 + f1) % 0xff);
c1 = 0xff - (( f0 + c0 ) % 0xff);
*/