/*
 * calamp_tracker.c
 *
 * Created: 27/06/2016 13:19:17
 *  Author: Thiago
 */ 

#include "calamp_tracker.h"

void calampTracker_sendATcommand(char *command) {
	usart1_putString(command);
}

void calampTracker_setAccumulator(uint8_t accumulator, uint32_t accumulatorValue) {
	char command[32];
	
	sprintf(&command,CALAMP_TRACKER_AT_SET_ACC,accumulator,accumulatorValue);
	calampTracker_sendATcommand(command);
}

void calampTracker_sendPegAction(uint8_t action, uint8_t modifier) {
	char command[32];
	
	sprintf(&command,CALAMP_TRACKER_AT_PEG_ACTION,action,modifier);
	calampTracker_sendATcommand(command);
}

uint32_t calampTracker_temperatureParser(int16_t value) {
	uint32_t rawTemp;
	
	if (value >= 0) {
		rawTemp = ((uint32_t) value);
	} else {
		rawTemp = (0xFFFF0000 | (uint32_t) value);
	}
	
	return rawTemp;
}

uint32_t calampTracker_ioStateParser(uint16_t outputs, uint16_t inputs) {
	
	return (((uint32_t) outputs << 16) | inputs);
}

void task_CalampTrackerResponseListener(uint8_t *responseBuffer) {
	
	uint8_t pointer = 0;
	char sentCommand[16];
	
	switch(calampResponseListenerState) {
		case INIT:
		
		break;
		
		case WAITING_RESPONSE:
		
		break;
		
		case GET_RESPONSE_COMMAND_TYPE: //GET_RESPONSE_COMMAND_TYPE
			pointer = strstr(responseBuffer,"\n\r");
		break;
	}
}