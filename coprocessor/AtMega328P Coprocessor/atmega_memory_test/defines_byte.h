/*
 * defines_byte.h
 *
 * Created: 22/01/2019 17:44:19
 *  Author: Eldad
 */ 


#ifndef DEFINES_BYTE_H_
#define DEFINES_BYTE_H_


#define AD_DDR		DDRA
#define AD_PORT		PORTA
#define AD_PIN		PINA

#define CONTROL_DDR		DDRB
#define CONTROL_PORT	PORTB
#define CONTROL_PIN		PINB

//active low:
// BHE RD WR
//port B to mega pinout:
//	B[0] -> 53
//	B[1] -> 52
//	B[2] -> 51
//	B[3] -> 50
//	B[4] -> 10
//	B[5] -> 11
//	B[6] -> 12
//	B[7] -> 13


#define BHE		0
#define ALE		1
#define RD		2
#define WR		3

#define BHE_ON()		CONTROL_PORT &= ~(1<<BHE)
#define BHE_OFF()		CONTROL_PORT |= (1<<BHE)
#define ALE_ON()	CONTROL_PORT |= (1<<ALE)
#define ALE_OFF()	CONTROL_PORT &= ~(1<<ALE)
#define RD_ON()		CONTROL_PORT &= ~(1<<RD)
#define RD_OFF()	CONTROL_PORT |= (1<<RD)
#define WR_ON()		CONTROL_PORT &= ~(1<<WR)
#define WR_OFF()	CONTROL_PORT |= (1<<WR)

#endif /* DEFINES_BYTE_H_ */