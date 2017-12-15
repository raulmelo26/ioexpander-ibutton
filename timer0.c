/**
 * @file timer0.c
 * @author Thiago - thiagosilva@trixlog.com
 * @copyright Trixlog
 * @date 28/01/2015
 * @version 1.0
 */

#include "timer0.h"

void timer0_init() {
	timer0_stop(); //Timer stopped
	timer0_setPreClock(TIMER0_CLKIO_BY_1024); //Prescalar 1024;
	timer0_setCounter(TIMER0_OVERFLOW);
	timer0_enableOverFlowInt(); //enable timer0 overflow interrupt;
}

ISR(TIMER0_OVF_vect) {
	timer0_setCounter(TIMER0_OVERFLOW);
	
	if (timeoutLoginEnable) {
		timeoutLogin++;
	}
	
	if (timeoutLogoutEnable) {
		timeoutLogout++;
	}
	
	if (timeoutWaitLoginEnable) {
		timeoutWaitLogin++;
	}
	timerOverflowCount++;
}
