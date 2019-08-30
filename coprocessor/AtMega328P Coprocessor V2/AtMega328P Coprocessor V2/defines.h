/*
 * File: defines.h
 * Project: AtMega328P Coprocessor V2
 *
 * Created: 5.2.2019 19:10:00
 * Author: Eldad Hellerman
 */ 

#ifndef DEFINES_H_
#define DEFINES_H_

#include <avr/io.h>

#define DDR(X) X##_DDR
#define PORT(X) X##_PORT
#define PIN(X) X##_PIN

#define SET_OUTPUT(X)	DDR(X) |= (1<<X##_BIT)
#define SET_INPUT(X)	DDR(X) &= ~(1<<X##_BIT)
#define SET_HIGH(X)		PORT(X) |= (1<<X##_BIT)
#define SET_LOW(X)		PORT(X) &= ~(1<<X##_BIT)
#define GET_INPUT(X)	(PIN(X) & (1<<X##_BIT))

#define SET_OUTPUT_LOW(X)	SET_OUTPUT(X); SET_LOW(X);
#define SET_OUTPUT_HIGH(X)	SET_OUTPUT(X); SET_HIGH(X);
#define SET_INPUT_LOW(X)	SET_INPUT(X); SET_LOW(X)
#define SET_INPUT_HIGH(X)	SET_INPUT(X); SET_HIGH(X)


#define BHE_IN_ADDRESS (((uint32_t)1)<<23)

/*connections:

UART_RX, UART_TX
ALE, RD, WR
CLK, RESET, HOLD, HLDA, TEST, READY, INTR, NMI, INTA
SPI_MOSI, SPI_MISO, SPI_SCK, SHREG_RCLK, SHREG_OE, SHREG_LD
				____________
UART TX		D.1|		    |
UART RX		D.0|	AVR		|C.5		READY
			C.6|	PRO		|C.4		TEST
			GND|	mini	|VCC
RD			D.2|			|C.3		NMI
WR			D.3|			|C.2		INTR
ALE			D.4|			|C.1		REG_SHLD
CLK			D.5|			|C.0		REG_OE
RESET		D.6|			|B.5		SCK
INTA		D.7|			|B.4		MISO
HOLD		B.0|			|B.3		MOSI
HLDA		B.1|____________|B.2		REG_RCLK

could be moved to secondary AVR (which will be responsible for IO):
	-INTA
	-NMI
	-INTR
	
*/

#define ALE			ALE
#define RD			RD
#define WR			WR
#define CLK			CLK
#define RESET		RESET
#define HOLD		HOLD
#define HLDA		HLDA
#define TEST		TEST
#define READY		READY
#define INTR		INTR
#define NMI			NMI
#define INTA		INTA
#define SPI_MOSI	SPI_MOSI
#define SPI_MISO	SPI_MISO
#define SPI_SCK		SPI_SCK
#define SHREG_RCLK	SHREG_RCLK
#define SHREG_OE	SHREG_OE
#define SHREG_LD	SHREG_LD


#define UART_RX_BIT			0
#define UART_RX_DDR			DDRD
#define UART_RX_PORT		PORTD
#define UART_RX_PIN			PIND
#define UART_TX_BIT			1
#define UART_TX_DDR			DDRD
#define UART_TX_PORT		PORTD
#define UART_TX_PIN			PIND
#define RD_BIT				2
#define RD_DDR				DDRD
#define RD_PORT				PORTD
#define RD_PIN				PIND
#define WR_BIT				3
#define WR_DDR				DDRD
#define WR_PORT				PORTD
#define WR_PIN				PIND
#define ALE_BIT				4
#define ALE_DDR				DDRD
#define ALE_PORT			PORTD
#define ALE_PIN				PIND
#define CLK_BIT				5
#define CLK_DDR				DDRD
#define CLK_PORT			PORTD
#define CLK_PIN				PIND
#define RESET_BIT			6
#define RESET_DDR			DDRD
#define RESET_PORT			PORTD
#define RESET_PIN			PIND
#define INTA_BIT			7
#define INTA_DDR			DDRD
#define INTA_PORT			PORTD
#define INTA_PIN			PIND
#define HOLD_BIT			0
#define HOLD_DDR			DDRB
#define HOLD_PORT			PORTB
#define HOLD_PIN			PINB
#define HLDA_BIT			1
#define HLDA_DDR			DDRB
#define HLDA_PORT			PORTB
#define HLDA_PIN			PINB

#define SHREG_RCLK_BIT		2
#define SHREG_RCLK_DDR		DDRB
#define SHREG_RCLK_PORT		PORTB
#define SHREG_RCLK_PIN		PINB
#define SPI_MOSI_BIT		3
#define SPI_MOSI_DDR		DDRB
#define SPI_MOSI_PORT		PORTB
#define SPI_MOSI_PIN		PINB
#define SPI_MISO_BIT		4
#define SPI_MISO_DDR		DDRB
#define SPI_MISO_PORT		PORTB
#define SPI_MISO_PIN		PINB
#define SPI_SCK_BIT			5
#define SPI_SCK_DDR			DDRB
#define SPI_SCK_PORT		PORTB
#define SPI_SCK_PIN			PINB
#define SHREG_OE_BIT		0
#define SHREG_OE_DDR		DDRC
#define SHREG_OE_PORT		PORTC
#define SHREG_OE_PIN		PINC
#define SHREG_LD_BIT		1
#define SHREG_LD_DDR		DDRC
#define SHREG_LD_PORT		PORTC
#define SHREG_LD_PIN		PINC
#define INTR_BIT			2
#define INTR_DDR			DDRC
#define INTR_PORT			PORTC
#define INTR_PIN			PINC
#define NMI_BIT				3
#define NMI_DDR				DDRC
#define NMI_PORT			PORTC
#define NMI_PIN				PINC
#define TEST_BIT			4
#define TEST_DDR			DDRC
#define TEST_PORT			PORTC
#define TEST_PIN			PINC
#define READY_BIT			5
#define READY_DDR			DDRC
#define READY_PORT			PORTC
#define READY_PIN			PINC


#define ALE_ON()		SET_HIGH(ALE)
#define ALE_OFF()		SET_LOW(ALE)
#define ALE_PULSE()		ALE_ON(); ALE_OFF()
#define RD_ON()			SET_LOW(RD)
#define RD_OFF()		SET_HIGH(RD)
#define WR_ON()			SET_LOW(WR)
#define WR_OFF()		SET_HIGH(WR)
#define OE_ON()			SET_LOW(SHREG_OE)
#define OE_OFF()		SET_HIGH(SHREG_OE)
#define RCLK_ON()		SET_HIGH(SHREG_RCLK)
#define RCLK_OFF()		SET_LOW(SHREG_RCLK)
#define RCLK_PULSE()	RCLK_ON(); RCLK_OFF()
#define LD_ON()			SET_LOW(SHREG_LD)
#define LD_OFF()		SET_HIGH(SHREG_LD)
#define LD_PULSE()		LD_ON(); LD_OFF()
#define RESET_ON()		SET_HIGH(RESET)
#define RESET_OFF()		SET_LOW(RESET)
#define HOLD_ON()		SET_HIGH(HOLD)
#define HOLD_OFF()		SET_LOW(HOLD)
#define TEST_ON()		SET_LOW(TEST)
#define TEST_OFF()		SET_HIGH(TEST)
#define READY_ON()		SET_HIGH(READY)
#define READY_OFF()		SET_LOW(READY)
#define INTR_ON()		SET_HIGH(INTR)
#define INTR_OFF()		SET_LOW(INTR)
#define NMI_ON()		SET_HIGH(NMI)
#define NMI_OFF()		SET_LOW(NMI)

#endif /* DEFINES_H_ */