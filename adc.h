/**
 * \file adc.h
 * \brief
 * \author Thiago - thiagosilva@trixlog.com
 * \copyright Trixlog
 * \date creation: 08/11/2012
 * \date updated: 14/03/2013
 * \version 1.0
 */

#ifndef ADC_H_
#define ADC_H_

/**
 * Includes
 */
#include <avr/io.h>

/**
 * Defines
 */

/**
 * Registers
 */
#define ADC_Multiplexer_Register		ADMUX
#define ADC_Control_Status_Register_A	ADCSRA
#define ADC_Control_Status_Register_B	ADCSRB
#define ADC_Data_Register				ADC
#define ADC_Data_Register_H				ADCH
#define ADC_Data_Register_L				ADCL
#define Digital_In_Dis_Register_0		DIDR0

/**
 * Voltage Reference Selections for ADC
 */
#if defined (__AVR_ATtiny1634__) || defined (__AVR_ATtiny84A__)
	#define VCC          (0<<REFS1 | 0<<REFS0)
	#define AREF		 (0<<REFS1 | 1<<REFS0)
	#define INTERNAL	 (1<<REFS1 | 0<<REFS0)
	#define RESERVED	 (1<<REFS1 | 1<<REFS0)
#else
	#define AREF		 (0<<REFS1 | 0<<REFS0)
	#define AVCC		 (0<<REFS1 | 1<<REFS0)
	#define RESERVED	 (1<<REFS1 | 0<<REFS0)
	#define INTERNAL	 (1<<REFS1 | 1<<REFS0)
#endif

/**
 * Single-Ended Input channel Selections
 */
#define ADC0		(0<<MUX3 | 0<<MUX2 | 0<<MUX1 | 0<<MUX0)
#define ADC1		(0<<MUX3 | 0<<MUX2 | 0<<MUX1 | 1<<MUX0)
#define ADC2		(0<<MUX3 | 0<<MUX2 | 1<<MUX1 | 0<<MUX0)
#define ADC3		(0<<MUX3 | 0<<MUX2 | 1<<MUX1 | 1<<MUX0)
#define ADC4		(0<<MUX3 | 1<<MUX2 | 0<<MUX1 | 0<<MUX0)
#define ADC5		(0<<MUX3 | 1<<MUX2 | 0<<MUX1 | 1<<MUX0)
#define ADC6		(0<<MUX3 | 1<<MUX2 | 1<<MUX1 | 0<<MUX0)
#define ADC7		(0<<MUX3 | 1<<MUX2 | 1<<MUX1 | 1<<MUX0)
#define ADC8		(1<<MUX3 | 0<<MUX2 | 0<<MUX1 | 0<<MUX0)
#define ADC9		(1<<MUX3 | 0<<MUX2 | 0<<MUX1 | 1<<MUX0)
#define ADC10		(1<<MUX3 | 0<<MUX2 | 1<<MUX1 | 0<<MUX0)
#define ADC11		(1<<MUX3 | 0<<MUX2 | 1<<MUX1 | 1<<MUX0)
#define CLEAR_ADMUX_BITS	0x0F

/**
 * ADC Prescaler Selections
 */
#define ADC_CLOCK_DIV2		(0<<ADPS2 | 0<<ADPS1 | 0<<ADPS0)
#define ADC_CLOCK_DIV2_		(0<<ADPS2 | 0<<ADPS1 | 1<<ADPS0)
#define ADC_CLOCK_DIV4		(0<<ADPS2 | 1<<ADPS1 | 0<<ADPS0)
#define ADC_CLOCK_DIV8		(0<<ADPS2 | 1<<ADPS1 | 1<<ADPS0)
#define ADC_CLOCK_DIV16		(1<<ADPS2 | 0<<ADPS1 | 0<<ADPS0)
#define ADC_CLOCK_DIV32		(1<<ADPS2 | 0<<ADPS1 | 1<<ADPS0)
#define ADC_CLOCK_DIV64		(1<<ADPS2 | 1<<ADPS1 | 0<<ADPS0)
#define ADC_CLOCK_DIV128	(1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0)


/**
 * Macros
 */
#define adc_enable()						{ADC_Control_Status_Register_A |= (1<<ADEN);}
#define adc_disable()						{ADC_Control_Status_Register_A &= ~(1<<ADEN);}
#define	adc_setPrescaler(divisionFactor)    {ADC_Control_Status_Register_A |= divisionFactor;}
#define adc_setReference(config)			{ADC_Multiplexer_Register |= (config); }
#define adc_setChannel(chanel)				{ADC_Multiplexer_Register |= (chanel); }
#define adc_clearChannel(chanel)			{ADC_Multiplexer_Register &= ~(chanel); }
#define adc_startConversion()				{ADC_Control_Status_Register_A |= (1<<ADSC); }
#define adc_isBusy()						(ADC_Control_Status_Register_A &(1<<ADSC))


/**
 * Prototype of function
 */
uint16_t adc_read(uint8_t channel);

#endif /* ADC_H_ */
