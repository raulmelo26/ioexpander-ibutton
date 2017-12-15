/*
 * _74hc595.h
 *
 * Created: 19/08/2016 16:17:29
 *  Author: Internet
 */ 


#ifndef _74hc595_H_
#define _74hc595_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

extern uint8_t registerData;

#define HC595_LATCH_PORT	PORTA
#define HC595_LATCH_DDR		DDRA
#define HC595_PORT			PORTC
#define HC595_DDR			DDRC

#define HC595_DS_POS		PORTC5      //Data pin (DS) pin location

#define HC595_SH_CP_POS		PORTC4      //Shift Clock (SH_CP) pin location
#define HC595_LATCH_POS		PORTA6      //Store Clock (ST_CP) pin location LATCH ? 

//Low level macros to change data (DS)lines
#define HC595DataHigh() (HC595_PORT|=(1<<HC595_DS_POS))

#define HC595DataLow() (HC595_PORT&=(~(1<<HC595_DS_POS)))

#define HC595_setPinData(pin) {registerData |= (1 << pin);}   // turn On the Pull-up
#define HC595_clrPinData(pin) {registerData &= ~(1 << pin);}   // turn On the Pull-up

#define HC595_Cleared	0x00	
#define HC595_S0		0
#define HC595_S1		1
#define HC595_S2		2
#define HC595_S3		3
#define HC595_KEY		4
#define HC595_CLK		5
#define HC595_E_OUT		6
#define HC595_RST_OUT	7

void HC595_init();
void HC595_pulse();
void HC595_latch();
void HC595_write(uint8_t data);
void HC595_setPin(uint8_t pin);
void HC595_clrPin(uint8_t pin);
void HC595_xorPin(uint8_t pin);

void HC595_wait();

#endif /* 74HC595_H_ */