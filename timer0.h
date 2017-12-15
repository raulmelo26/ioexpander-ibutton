/**
 * @file timer0.h
 * @author Thiago - thiagosilva@trixlog.com
 * @copyright Trixlog
 * @date 28/01/2015
 * @version 1.0
 */

/**
 * Includes
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER0_OVERFLOW					(255 - 156)
#define TIMER0_CLKIO_BY_256				(0<<CS02)|(1<<CS01)|(0<<CS00)
#define TIMER0_CLKIO_BY_1024			(1<<CS02)|(0<<CS01)|(1<<CS00)

#define timer0_setPreClock(config)		{TCCR0B |= config;}
#define timer0_setCounter(value)		{TCNT0 = value;}
#define timer0_enableOverFlowInt()		{TIMSK |= (1<<TOIE0);}
#define timer0_stop()					{TCCR0B |= (0<<CS02)|(0<<CS01)|(0<<CS00);}

uint16_t timerOverflowCount;		
uint8_t timeoutLoginEnable;
uint16_t timeoutLogin;	

uint8_t timeoutLogoutEnable;
uint16_t timeoutLogout;

uint8_t timeoutWaitLoginEnable;
uint16_t timeoutWaitLogin;

void timer0_init();