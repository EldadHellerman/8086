/*
 * defines.h
 *
 * Created: 22/01/2019 17:18:57
 *  Author: Eldad
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_


#define AD_HIGH_DDR		DDRC
#define AD_HIGH_PORT	PORTC
#define AD_HIGH_PIN		PINC

#define AD_LOW_DDR		DDRA
#define AD_LOW_PORT		PORTA
#define AD_LOW_PIN		PINA

#define CONTROL_DDR		DDRB
#define CONTROL_PORT	PORTB
#define CONTROL_PIN		PINB

#define BHE		0
#define ALE		1
#define RD		2
#define WR		3
#define	HOLD	4
#define	HLDA	5
#define RST		6

//BHE RD WR - Active Low
#define BHE_ON()	CONTROL_PORT &= ~(1<<BHE)
#define BHE_OFF()	CONTROL_PORT |= (1<<BHE)
#define ALE_ON()	CONTROL_PORT |= (1<<ALE)
#define ALE_OFF()	CONTROL_PORT &= ~(1<<ALE)
#define RD_ON()		CONTROL_PORT &= ~(1<<RD)
#define RD_OFF()	CONTROL_PORT |= (1<<RD)
#define WR_ON()		CONTROL_PORT &= ~(1<<WR)
#define WR_OFF()	CONTROL_PORT |= (1<<WR)
#define HOLD_ON()	CONTROL_PORT |= (1<<HOLD)
#define HOLD_OFF()	CONTROL_PORT &= ~(1<<HOLD)
#define RESET_ON()	CONTROL_PORT |= (1<<RST)
#define RESET_OFF()	CONTROL_PORT &= ~(1<<RST)

#define CONTROL2_DDR	DDRG
#define CONTROL2_PORT	PORTG
#define CONTROL2_PIN	PING

#define INTR	0
#define INTA	1

#define INTR_ON()	CONTROL2_PORT |= (1<<INTR)
#define INTR_OFF()	CONTROL2_PORT &= ~(1<<INTR)

#endif /* DEFINES_H_ */