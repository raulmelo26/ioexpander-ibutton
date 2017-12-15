/*
 * calamp_tracker.h
 *
 * Created: 27/06/2016 13:15:00
 *  Author: Thiago
 */ 


#ifndef CALAMP_TRACKER_H_
#define CALAMP_TRACKER_H_

#include <avr/io.h>
#include <string.h>
#include "usart.h"

#define CALAMP_TRACKER_AT_GET_ESN		"AT$APP ESN?\r"
#define CALAMP_TRACKER_AT_SET_ACC		"AT$APP PARAM 2560,%u,%lu\r"
#define CALAMP_TRACKER_AT_PEG_ACTION	"AT$APP PEG ACTION %u %u\r"

#define PEG_ACTION_SEND_REPORT			1
#define PEG_ACTION_SET_OUTPUT			8
#define PEG_ACTION_CLEAR_OUTPUT			9
#define PEG_ACTION_MULTIPULSE_OUTPUT	80
#define PEG_ACTION_BLINK_OUTPUT_4HZ		12

#define ACTION_MODIFIER_IBUTTON_LOGIN	66
#define ACTION_MODIFIER_IBUTTON_LOGOUT	62

enum {
	ACC1,
	ACC2,
	ACC3,
	TEMPERATURE0 = 4,
	TEMPERATURE1 = 5,
	IBUTTON1,
	IBUTTON2,
	ACC8,
	ACC9,
	ACC10,
	ACC11,
	ACC12,
	ACC13,
	ACC14,
	IO_STATE,
	ACC16
};	


typedef struct {
	uint32_t esn;
	struct accumulators {
		uint32_t acc1;
		uint32_t acc2;
		uint32_t acc3;
		uint32_t acc4;
		uint32_t acc5;
		uint32_t acc6;
		uint32_t acc7;
		uint32_t acc8;
		uint32_t acc9;
		uint32_t acc10;
		uint32_t acc11;
		uint32_t acc12;
		uint32_t acc13;
		uint32_t acc14;
		uint32_t acc15;
		uint32_t acc16;
	};
} CalampTracker;


enum ResponseListenerStates{
	INIT,
	WAITING_RESPONSE,
	GET_RESPONSE_COMMAND_TYPE
};

enum ResponseListenerStates calampResponseListenerState;

void calampTracker_sendATcommand(char *command);
void calampTracker_setAccumulator(uint8_t accumulator, uint32_t value);
void calampTracker_sendPegAction(uint8_t action, uint8_t modifier);
uint32_t calampTracker_temperatureParser(int16_t value);
uint32_t calampTracker_ioStateParser(uint16_t outputs, uint16_t inputs);
void task_CalampTrackerResponseListener(uint8_t* responseBuffer);

#endif /* CALAMP_TRACKER_H_ */