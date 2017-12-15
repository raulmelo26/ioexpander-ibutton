/**
 * \file adc.c
 * \brief
 * \author Thiago - thiagosilva@trixlog.com
 * \copyright Trixlog
 * \date 08/11/2012
 * \version 1.0
 */

/**
 * Includes
 */
#include "adc.h"

/**
 * Definition of functions
 */

/**
 * \fn adc_read(channel)
 * \brief Read ad channel
 * \param channel(variable type uint8_t)
 * \return value of analogic digital conversion (variable type uint16_t)
 */
uint16_t adc_read(uint8_t channel)
{
	uint16_t result;
	ADC_Multiplexer_Register &= ~(CLEAR_ADMUX_BITS);
	adc_setChannel(channel);
	adc_startConversion();
	while(adc_isBusy());
	result = ADC_Data_Register;
	return result;
}




