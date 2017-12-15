/*
 * ibutton.h
 *
 *  Created on: 23 de jan de 2016
 *      Author: thiagosilva
 */

#ifndef IBUTTON_H_
#define IBUTTON_H_

#define F_CPU 8000000UL	// Oscillator frequency.

#include <avr/io.h>
#include <avr/delay.h>

#define IBUTTON_REGISTER_DDR	DDRC
#define IBUTTON_REGISTER_PORT	PORTC
#define IBUTTON_REGISTER_INPUT	PINC
#define IBUTTON_REGISTER_PIN	(2)	

//ibutton presence states
#define IBUTTON_NOT_PRESENT      0
#define IBUTTON_PRESENT          1

#define IBUTTON_ONEWIRE_FAMILY	0x01

uint8_t ibutton_getPresence();
uint8_t ibutton_getBit();
void 	ibutton_sendBit(uint8_t bit);
void 	ibutton_readButton(uint8_t* data);

#endif /* IBUTTON_H_ */
