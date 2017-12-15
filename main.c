/*
 * ibutton.c
 *
 * Created: 07/12/2017 16:29:34
 * Author : admin
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "74hc595.h"
#include "io.h"
#include "usart.h"
#include "ibutton.h"
#include "calamp_tracker.h"
#include "adc.h"
#include "timer0.h"

#define ADC_REF_IGN				110
#define TIMEOUT_LOGIN			1000
#define TIMEOUT_LOGOUT			500
#define TIMEOUT_WAIT_LOGIN		1000

union {
	uint8_t id[8];
	uint32_t idParts[2];
} ibuttonId;

uint8_t ignition;
uint8_t lastIgnition;
uint8_t driverLogged;
uint16_t adcResult;

uint8_t flag = 0;
uint8_t count = 0;
uint8_t n1 = 5;

int main(void) {

	io_init();
	
	HC595_init();
	HC595_write(HC595_Cleared);
	HC595_setPin(0);
	HC595_setPin(1);
	HC595_setPin(HC595_S0);
	HC595_setPin(HC595_S2);

	USART1_Init(BAUD_115200);
	
	adc_setPrescaler(ADC_CLOCK_DIV16);
	adc_setReference(VCC);
	adc_enable();
	
	timer0_init();
	
	sei();
	while(1) {
		_delay_ms(2000);
		lastIgnition = ignition;
		adcResult = adc_read(ADC0);
		ignition = (adcResult > 110)? 1 : 0;
		
		// Reenviar código ibutton
		 if (timerOverflowCount>=470)
		 {
			 if(flag && ignition){
				 calampTracker_setAccumulator(IBUTTON1, ibuttonId.idParts[1]);_delay_ms(2000);
				 calampTracker_setAccumulator(IBUTTON2, ibuttonId.idParts[0]);
				 count = (flag = (count >= 5) ? 0:6); 
				 count -= n1;
				 n1--;
				 
			 }
			 timerOverflowCount=0;
			 
		 }
		
		if (ignition) {
			HC595_setPin(HC595_S3);
			} else {
			HC595_clrPin(HC595_S3);
		}
		
		if (ibutton_getPresence() && driverLogged == 0) {
			ibutton_readButton(&ibuttonId.id);
			
			if (ibuttonId.id[0] == IBUTTON_ONEWIRE_FAMILY) { // its a 1-wire device family registered
				calampTracker_setAccumulator(IBUTTON1, ibuttonId.idParts[1]);_delay_ms(2000);
				calampTracker_setAccumulator(IBUTTON2, ibuttonId.idParts[0]);_delay_ms(2000);
				calampTracker_sendPegAction(PEG_ACTION_SEND_REPORT, ACTION_MODIFIER_IBUTTON_LOGIN);_delay_ms(2000);
				HC595_clrPin(HC595_S2);
				calampTracker_sendPegAction(PEG_ACTION_CLEAR_OUTPUT, 0);_delay_ms(2000);
				calampTracker_sendPegAction(PEG_ACTION_CLEAR_OUTPUT, 1);_delay_ms(2000);
				//calampTracker_sendPegAction(PEG_ACTION_MULTIPULSE_OUTPUT,20); //Antes estava assim: calampTracker_sendPegAction(PEG_ACTION_MULTIPULSE_OUTPUT,1);
				driverLogged = 1;
				flag = 1;
				n1=5;
				/*if(ignition){
					flag = 1;
					n1=5;
				}*/
				
				if (!ignition) {
					timeoutLogin = 0;
					timeoutLoginEnable = 1;
				}
				
				timeoutWaitLogin = 0;
				timeoutWaitLoginEnable = 0;
			}
			
		}
		
		if (ignition == 1 && lastIgnition == 0 && driverLogged == 0) {
			calampTracker_sendPegAction(PEG_ACTION_BLINK_OUTPUT_4HZ, 0);_delay_ms(2000);
			timeoutWaitLogin = 0;
			timeoutWaitLoginEnable = 1;
		}
		
		if (ignition == 0 && lastIgnition == 1 && driverLogged == 0) {
			calampTracker_sendPegAction(PEG_ACTION_CLEAR_OUTPUT, 0);_delay_ms(2000);
			calampTracker_sendPegAction(PEG_ACTION_CLEAR_OUTPUT, 1);_delay_ms(2000);
			timeoutWaitLoginEnable = 0;
		}
		
		if (ignition == 0 && lastIgnition == 1 && driverLogged == 1) {
			timeoutLogout = 0;
			timeoutLogoutEnable = 1;
		}
		
		if (ignition == 1 && lastIgnition == 0 && driverLogged == 1) {
			timeoutLoginEnable = 0;
			timeoutLogoutEnable = 0;
		}
		
		if (timeoutLoginEnable == 1 && timeoutLogin > TIMEOUT_LOGIN) {
			flag = 0;
			calampTracker_setAccumulator(IBUTTON1, 0);_delay_ms(2000);
			calampTracker_setAccumulator(IBUTTON2, 0);_delay_ms(2000);
			calampTracker_sendPegAction(PEG_ACTION_SEND_REPORT, ACTION_MODIFIER_IBUTTON_LOGOUT);_delay_ms(2000);
			HC595_setPin(HC595_S2);
			calampTracker_sendPegAction(PEG_ACTION_SET_OUTPUT, 1);_delay_ms(2000);
			//calampTracker_sendPegAction(PEG_ACTION_MULTIPULSE_OUTPUT,20); //Antes estava assim: calampTracker_sendPegAction(PEG_ACTION_MULTIPULSE_OUTPUT,1);
			driverLogged = 0;
			timeoutLoginEnable = 0;
		}
		
		if (timeoutLogoutEnable == 1 && timeoutLogout > TIMEOUT_LOGOUT) {
			flag = 0;
			calampTracker_setAccumulator(IBUTTON1, 0);_delay_ms(2000);
			calampTracker_setAccumulator(IBUTTON2, 0);_delay_ms(2000);
			calampTracker_sendPegAction(PEG_ACTION_SEND_REPORT, ACTION_MODIFIER_IBUTTON_LOGOUT);_delay_ms(2000);
			HC595_setPin(HC595_S2);
			calampTracker_sendPegAction(PEG_ACTION_SET_OUTPUT, 1);_delay_ms(2000);
			//calampTracker_sendPegAction(PEG_ACTION_MULTIPULSE_OUTPUT,20); //Antes estava asssim: calampTracker_sendPegAction(PEG_ACTION_MULTIPULSE_OUTPUT,1);
			driverLogged = 0;
			timeoutLoginEnable = 0;
			timeoutLogoutEnable = 0;
		}
		
		if (timeoutWaitLoginEnable == 1 && timeoutWaitLogin > TIMEOUT_WAIT_LOGIN) {
			calampTracker_sendPegAction(PEG_ACTION_SET_OUTPUT, 1);_delay_ms(2000);
			timeoutWaitLoginEnable = 0;
		}
		
	}
}

