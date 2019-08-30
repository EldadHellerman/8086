/*
 * File: main.c
 * Project: Programmer
 *
 * Created on: 25.1.2019
 * Author: Eldad Hellerman
 */


#include "stdio.h"
#include "stdlib.h"
#include "mem.h"
#include "string.h"
#include "unistd.h"
#include "time.h"
#include "stdbool.h"
#include "serial.h"

typedef unsigned char byte;

struct parameters{
	int baud_rate;
	int com_port;
	char *output_file_path;
	char *input_file_path;
	int interrupt_number;
	int memory_start;
	int memory_length;
	int block_number;
} static current_parameters;

typedef struct{
	char *name;
	void ( *cb)(void);
} function;

void write_uint32(char *buffer, unsigned int num){
	buffer[0] = (num>>24) & 0xff;
	buffer[1] = (num>>16) & 0xff;
	buffer[2] = (num>> 8) & 0xff;
	buffer[3] = (num>> 0) & 0xff;
}

void wait_for_ack(void){
	char buffer;
	do serial_read(&buffer, 1); while(buffer != 6);
}

void start_serial(void){
	serial_open(current_parameters.com_port, current_parameters.baud_rate);
}

boolean send_char(char c){
	return(serial_write(&c, 1) != 1);
}

boolean send_command(char cmd){
	boolean r = (serial_write(&cmd, 1) != 1);
	//wait_for_ack();
	return(r);
}

boolean send_uint32(unsigned int num){
	char buffer[4];
	buffer[0] = (num>>24) & 0xff;
	buffer[1] = (num>>16) & 0xff;
	buffer[2] = (num>> 8) & 0xff;
	buffer[3] = (num>> 0) & 0xff;
	boolean r = (serial_write(buffer, 4) != 4);
	return(r);
}

void upload(){
	struct parameters *p = &current_parameters;
	FILE *file;
	char buffer[1024*1024];

	//printf("uploading %s through com %d at %d\n",p->input_file_path, p->com_port, p->baud_rate);
	if(p->input_file_path == NULL){
		printf("\tERROR, input file not specified!\n");
		return;
	}
	file = fopen(p->input_file_path,"rb");
	if(file == NULL){
		printf("\tError! file wasn't found\n");
		return;
	}
	fseek(file, 0, SEEK_END);
	int file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	if(file_size > 1024*1024){
		printf("\tERROR! File is too big");
		fclose(file);
		return;
	}
	if(fread(buffer,1,file_size,file) != file_size){
		printf("\tERROR! could not read file completely\n");
		fclose(file);
		return;
	}
	printf("\tread file, size: %d\n",file_size);
	fclose(file);

	start_serial();
	boolean ok = false;
	do{
		if(send_command('p')) break;
		if(send_command('u')) break;
		if(send_uint32(p->memory_start)) break;
		if(send_uint32(file_size)) break;
		ok = true;
	}while(0);
	if(!ok){
		printf("\tERROR, cannot initiate communication\n");
		return;
	}
	int wrote = 0;
	while(wrote < file_size){
		int w = serial_write(buffer+wrote, (file_size-wrote > 256) ? 256 : (file_size-wrote));
		if(!w){ wrote = 0; break;}
		wrote += w;
		wait_for_ack();
	}
	if(wrote == 0){
		printf("\tERROR, serial communication error\n");
		return;
	}

	ok = false;
	do{
		if(send_command('r')) break;
		//if(send_command('c')) break; //////////////////////////////////////XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx
		ok = true;
	}while(0);
	if(!ok){
		printf("\tERROR, cannot initiate communication\n");
		return;
	}
	printf("\tProgrammed successfully!\n");
	serial_close();
}

void dump(){
	struct parameters *p = &current_parameters;
	//printf("dumping memory through com %d at %d",p->com_port, p->baud_rate);
	int start = 0, length = 64*1024;

	if(!(p->memory_start == 0 && p->memory_length == 0)){
		start = p->memory_start;
		length = p->memory_length;
	}

	char buffer[length];
	start_serial();
	boolean ok = false;
	do{
		if(send_command('p')) break;
		if(send_command('m')) break;
		if(send_uint32(start)) break;
		if(send_uint32(length)) break;
		ok = true;
	}while(0);
	if(!ok){
		printf("ERROR, cannot initiate communication\n");
		return;
	}
	int read = 0;
	while(read < length){
		int r = serial_read(buffer, length);
		if(!r){ read = 0; break;}
		read += r;
	}
	if(read == 0){
		printf("ERROR, serial communication error\n");
		return;
	}
	/*if(send_command('c')){ /////////////////////////XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		printf("ERROR, cannot initiate communication\n");
		return;
	}*/
	printf("Memory was read successfully!\n");
	serial_close();

	if(p->output_file_path == NULL){
		for(int i=0; i<length; i++){
			if((i%16) == 0) printf("%03X:    ",i);
			if(((i%16) == 15)) printf("%.2X\n", ((int)buffer[i])&0xff);
			else printf("%.2X,", ((int)buffer[i])&0xff);
			//printf(((i%16) == 15) ? "%.2X\n" : "%.2X,", ((int)buffer[i])&0xff);
		}
	}else{
		FILE *file;
		file = fopen(p->output_file_path,"wb+");
		if(file == NULL){
			printf("Error! can't write to file\n");
			return;
		}
		if(fwrite(buffer,1,length,file) != length){
			printf("ERROR! could not write file completely\n");
			fclose(file);
			return;
		}
		printf("wrote to file!\n");
		fclose(file);
	}
}

void interrupt(void){
	struct parameters *p = &current_parameters;
	boolean ok = false;
	start_serial();
	do{
		if(send_command('i')) break;
		if(send_char((unsigned char)p->interrupt_number)) break;
		ok = true;
	}while(0);
	if(!ok){
		printf("ERROR, cannot send interrupt\n");
		return;
	}
	serial_close();
}

void erase(void){
	struct parameters *p = &current_parameters;
	unsigned int address = p->memory_start;
	if(p->block_number != -1){
		switch(p->block_number){
			case 1: address = 0x80000; break;
			case 2: address = 0xA0000; break;
			case 3: address = 0xC0000; break;
			case 4: address = 0xE0000; break;
			case 5: address = 0xF8000; break;
			case 6: address = 0xFA000; break;
			case 7: address = 0xFC000; break;
			default:
				printf("ERROR, invalid block number\n");
				return;
		}
	}
	start_serial();
	boolean ok = false;
	do{
		if(send_command('e')) break;
		if(send_uint32(address)) break;
		ok = true;
	}while(0);
	if(!ok){
		printf("ERROR, cannot erase memory\n");
		return;
	}
	serial_close();
	printf("erased successfully!\n");
}

#define CLI_FUNCTION(X)	{.name = #X, .cb = X}

function functions[] = {
		CLI_FUNCTION(upload),
		CLI_FUNCTION(dump),
		CLI_FUNCTION(interrupt),
		CLI_FUNCTION(erase)
};

int number_of_functions = 4;

void serial_test(){
	char rx[15000];
	char tx[3] = "b";
	printf("opening\n");
	serial_open(5,230400);

	printf("writing b\n");
	serial_write(tx,1);
	printf("reading...");
	int read = serial_read(rx, 15000);
	printf("read %d bytes\n",read);
	printf("closing\n");
	serial_close();
	printf("printing:\n");
	printf("%.*s",read,rx);
}

void print_help_menu(void){
	printf("--------------------------------------------------\n");
	printf("8086 Programer\nWritten by EH\nA utility for interfacing with the 8086 board\n\n");
	printf("Usage: Programer.exe function [options]\n");
	printf("Functions:\n");
	printf("\tupload - uploading input file to board\n");
	printf("\tdump - dumping memory to terminal or to output file\n");
	printf("\tinterrupt - generate an interrupt\n");
	printf("Options:\n");
	printf("\t-c <com_port>, --baudrate <com_port>      Sets the COM port\n");
	printf("\t-b <baud_rate>, --baudrate <baud_rate>    Sets the baud rate\n");
	printf("\t-o <output_path>                          Sets the output path\n");
	printf("\t-i <input_path>                           Sets the input path\n");
	printf("\t-interrupt <interrupt number>             Sets the interrupt number\n");
	printf("--------------------------------------------------\n");
}

void parse_parameters(int argc, char **args){
	char *parameter;
	int length;
	function *main_func = NULL;
	int error = 0;
	//struct parameters = NULL;
	for(int i=0; i<argc; i++){
		parameter = args[i];
		length = strlen(parameter);
		//printf("%d (%d): %s\n",i,length,parameter);
		if(parameter[0] == '-'){
			if(length >= 2 && parameter[1] == '-'){
				if(length < 3){ error = 1; break;}
				if(strncasecmp(&parameter[2],"comport",strlen("comport")) == 0){
					if(sscanf(&parameter[2 + strlen("comport")],"%d",&current_parameters.com_port) == 0) error = 3;
				}else if(strncasecmp(&parameter[2],"baudrate",strlen("baudrate")) == 0){
					if(sscanf(&parameter[2 + strlen("baudrate")],"%d",&current_parameters.baud_rate) == 0) error = 4;
				}else if(strncasecmp(&parameter[2],"interrupt",strlen("interrupt")) == 0){
					if(sscanf(&parameter[2 + strlen("interrupt")],"%d",&current_parameters.interrupt_number) == 0) error = 9;
				}else if(strncasecmp(&parameter[2],"from",strlen("from")) == 0){
					if(sscanf(&parameter[2 + strlen("from")],"%d",&current_parameters.memory_start) == 0) error = 10;
				}else if(strncasecmp(&parameter[2],"length",strlen("length")) == 0){
					if(sscanf(&parameter[2 + strlen("length")],"%d",&current_parameters.memory_length) == 0) error = 11;
				}else if(strncasecmp(&parameter[2],"block",strlen("block")) == 0){
					if(sscanf(&parameter[2 + strlen("block")],"%d",&current_parameters.block_number) == 0) error = 12;
				}
				if(error) break;
			}else{
				if(length < 2){ error = 2; break;}
				switch(parameter[1]){
				case 'c':
					if(sscanf(&parameter[2],"%d",&current_parameters.com_port) == 0) error = 5;
					break;
				case 'b':
					if(sscanf(&parameter[2],"%d",&current_parameters.baud_rate) == 0) error = 6;
					break;
				case 'o':
					if(length < 3){ error = 7; break;}
					current_parameters.output_file_path = &parameter[2];
					break;
				case 'i':
					if(length < 3){ error = 8; break;}
					current_parameters.input_file_path = &parameter[2];
					break;
				}
				if(error) break;
			}
		}else{
			for(int i=0; i<number_of_functions; i++) if(strcasecmp(functions[i].name,parameter) == 0) main_func = &functions[i];
			/*if(strcasecmp("upload",args[1]) == 0){ //use strcmp that doesnt care about capital letter maybe?

			}else if(strcmp("dump",args[1]) == 0){ //use strcmp that doesnt care about capital letter maybe?
				printf("dumping memory\n");
			}*/
			//first go through parameters and search parameter beginning with -, as in -b --baudrate, -c --comport, etc
			//and in that pass mark the location of main parameters - as in upload, program, help, terminal, etc
			//than the following will be on first main parameter, and not on all parameters.
			//as in: instead of args[1], it will be args[main_args[0]], args[main_args[1]], etc..
			//and maybe mark options also as args[option_args[0]], with its data at args[option_args[0] + 1]
		}
	}
	if(error){
		printf("there was an error (#%d)\n",error);
		return;
	}
	if(main_func != NULL){
		main_func->cb();
	}

}

int main(int argc, char **args){
	//serial_test();
	if(argc == 1){
		print_help_menu();
		return(EXIT_SUCCESS);
	}
	//printf("argc is %d\n",argc);
	current_parameters.output_file_path = NULL;
	current_parameters.input_file_path = NULL;
	current_parameters.interrupt_number = 0;
	current_parameters.memory_start = 0;
	current_parameters.memory_length = 0;
	current_parameters.block_number = -1;
	parse_parameters(argc-1,args+1);
	return(EXIT_SUCCESS);
}

