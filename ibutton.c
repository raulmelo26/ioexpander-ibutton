/*
 * ibutton.c
 *
 *  Created on: 23 de jan de 2016
 *      Author: thiagosilva
 */

#include "ibutton.h"

uint8_t ibutton_getPresence() {
	uint8_t isPresent;
	
	IBUTTON_REGISTER_PORT |= (1<<IBUTTON_REGISTER_PIN);
	
    //master reset pulse - pull line low and wait for 480uS
    IBUTTON_REGISTER_DDR |= (1<<IBUTTON_REGISTER_PIN); //set line as output
    IBUTTON_REGISTER_PORT &= ~(1<<IBUTTON_REGISTER_PIN); //put line low
	_delay_us(480);
	 
    //release the line and wait 60us
	IBUTTON_REGISTER_PORT |= (1<<IBUTTON_REGISTER_PIN);
    IBUTTON_REGISTER_DDR &= ~(1<<IBUTTON_REGISTER_PIN); //set line as input
	_delay_us(80);
	 
	//read the iButton presence pulse (low level)
    isPresent = (IBUTTON_REGISTER_INPUT & (1<<IBUTTON_REGISTER_PIN)); 
	_delay_us(400);
	
	IBUTTON_REGISTER_PORT |= (1<<IBUTTON_REGISTER_PIN);
	 
    //return presence status
    if (isPresent) {
		return IBUTTON_NOT_PRESENT;
	} else {
		return IBUTTON_PRESENT;
	}
}

uint8_t ibutton_getBit() {
    uint8_t bit = 0;
	
	IBUTTON_REGISTER_PORT |= (1<<IBUTTON_REGISTER_PIN);
	 
    //pull line low for 1us
    IBUTTON_REGISTER_DDR |= (1<<IBUTTON_REGISTER_PIN); //set line as output
    IBUTTON_REGISTER_PORT &= ~(1<<IBUTTON_REGISTER_PIN);
	_delay_us(1);
	
    //release the line, and read the iButton data bit
    IBUTTON_REGISTER_PORT |= (1<<IBUTTON_REGISTER_PIN);
	IBUTTON_REGISTER_DDR &= ~(1<<IBUTTON_REGISTER_PIN); //set line as input (release the line)
	_delay_us(14);
	 
	//read line value, wait for 45uS to end and return read value	
    bit = (IBUTTON_REGISTER_INPUT & (1<<IBUTTON_REGISTER_PIN));
	_delay_us(45);
	
	IBUTTON_REGISTER_PORT |= (1<<IBUTTON_REGISTER_PIN);
	 
    //return the data bit value
    if (bit) {
		return 0x80;
	} else {
		return 0;
	}
}

void ibutton_sendBit(uint8_t bit) {
	IBUTTON_REGISTER_PORT |= (1<<IBUTTON_REGISTER_PIN);
	
    // pull line low for 1uS
	IBUTTON_REGISTER_PORT &= ~(1<<IBUTTON_REGISTER_PIN);
	IBUTTON_REGISTER_DDR |= (1<<IBUTTON_REGISTER_PIN); //set line as output
	_delay_us(1);
	
    //if we want to write 1, release the line (if not will keep low)
    if (bit) {
		IBUTTON_REGISTER_PORT |= (1<<IBUTTON_REGISTER_PIN);
		IBUTTON_REGISTER_DDR &= ~(1<<IBUTTON_REGISTER_PIN); //set line as input (release the line)
	}
	//Wait for 60uS and release the line
	_delay_us(60);
	
	//release the line
    IBUTTON_REGISTER_DDR &= ~(1<<IBUTTON_REGISTER_PIN); //set line as input
	
	IBUTTON_REGISTER_PORT |= (1<<IBUTTON_REGISTER_PIN);
}

void ibutton_readButton(uint8_t* data) {
	uint8_t tmp,i;

    //send 'read ROM command'
    i = 0x33;
    for (tmp=0;tmp<8;tmp++) {
		ibutton_sendBit(i&0x01);
		i >>= 1;
    }

    //get the iButton Data
    for (i=0;i<8;i++) {
		*data = 0; //init variable
		for (tmp=0;tmp<8;tmp++) {
			*data >>= 1;
			*data |= ibutton_getBit();
		}
		data++;
    }
}

