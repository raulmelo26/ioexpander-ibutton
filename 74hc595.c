/*
 * 74hc595.c
 *
 * Created: 19/08/2016 17:14:42
 *  Author: SOLON
 */ 

#include "74hc595.h"

uint8_t registerData = 0x00;

//Initialize HC595 System

void HC595_init() {
   //Make the Data(DS), Shift clock (SH_CP), Store Clock (ST_CP) lines output
   HC595_DDR|=((1<<HC595_SH_CP_POS)|(1<<HC595_DS_POS));
   HC595_LATCH_DDR |= (1<<HC595_LATCH_POS);
}

//Sends a clock pulse on SH_CP line
void HC595_pulse() {
   //Pulse the Shift Clock
   HC595_PORT|=(1<<HC595_SH_CP_POS);//HIGH
   HC595_PORT&=(~(1<<HC595_SH_CP_POS));//LOW

}

//Sends a clock pulse on ST_CP line
void HC595_latch() {
   //Pulse the Store Clock
   HC595_LATCH_PORT|=(1<<HC595_LATCH_POS);//HIGH
   HC595_LATCH_PORT&=(~(1<<HC595_LATCH_POS));//LOW
}


/*

Main High level function to write a single byte to
Output shift register 74HC595. 

Arguments:
   single byte to write to the 74HC595 IC

Returns:
   NONE

Description:
   The byte is serially transfered to 74HC595
   and then latched. The byte is then available on
   output line Q0 to Q7 of the HC595 IC.

*/

void HC595_setPin(uint8_t pin) {
	HC595_setPinData(pin);
	HC595_write(registerData);
}

void HC595_clrPin(uint8_t pin) {
	HC595_clrPinData(pin);
	HC595_write(registerData);
}

void HC595_xorPin(uint8_t pin) {
	registerData ^= (1 <<  pin);
	HC595_write(registerData);
}

void HC595_write(uint8_t data) {
   //Send each 8 bits serially

   //Order is MSB first
   for(uint8_t i=0;i<8;i++)
   {
      //Output the data on DS line according to the
      //Value of MSB
      if(data & 0b10000000)
      {
         //MSB is 1 so output high

         HC595DataHigh();
      }
      else
      {
         //MSB is 0 so output high
         HC595DataLow();
      }

      HC595_pulse();  //Pulse the Clock line
      data=data<<1;  //Now bring next bit at MSB position

   }

   //Now all 8 bits have been transferred to shift register
   //Move them to output latch at one
   HC595_latch();
}

