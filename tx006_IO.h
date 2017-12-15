/*
 * tx006_IO.h
 *
 * Created: 25/08/2016 09:41:24
 *  Author: SOLON
 */ 


#ifndef TX006_IO_H_
#define TX006_IO_H_

#include <avr/io.h>

#define IO_setup_EA0_Input()	{ 	\
	DDRA &= ~(1 << PORTA3); \
	DDRB |= (1 << PORTB3 ); \
	PORTB &= ~(1 << PORTB3 ); \
}
#define IO_setup_EA0_OutPut()	{   \
	DDRA &= ~(1 << PORTA3);\
	DDRB |= (1 << PORTB3 );\
}

#define IO_EA0_OutPut_HIGH(){\
	PORTB |= (1 << PORTB3 );\
}

#define IO_EA0_OutPut_LOW(){\
	PORTB &= ~(1 << PORTB3 );\
}
								
#define	IO_setup_EA1_Input(){ \
	DDRA &= ~(1 << PORTA4);\
	DDRC |= (1 << PORTC0 );\
	PORTC &= ~(1 << PORTC0 );	\
}		

#define IO_setup_EA1_OutPut()	{\
	DDRA &= ~(1 << PORTA4);\
	DDRC |= (1 << PORTC0 );\
}	


#define IO_EA1_OutPut_HIGH(){\
	PORTC |= (1 << PORTC0 );\
}

#define IO_EA1_OutPut_LOW(){\
	PORTC &= ~(1 << PORTC0);\
}					
							
#define	IO_setup_ED0_Input(){\
	DDRA &= ~(1 << PORTA2);\
	PUEA |= (1 << PUEA2);\
	PORTA |= (1 << PORTA2);\
	DDRA |= (1 << PORTA5);\
	PORTA &= ~(1 << PORTA5);\
}
	
#define IO_setup_ED0_OutPut() {\
	DDRA &= ~(1 << PORTA2);\
	DDRA |= (1 << PORTA5);\
}


#define IO_ED0_OutPut_HIGH(){\
	PORTA |= ( 1 << PORTA5 );\
}

#define IO_ED0_OutPut_LOW(){\
	PORTA &= ~(1 << PORTA5);\
}


#define IO_ED0_PullUp_Enable(){\
	PUEA |= (1 << (2));\
}

#define IO_ED0_PullUp_Disable(){\
	PUEA &= ~(1 << (2));\
}

#define	IO_setup_ED1_Input() {\
	DDRA &= ~(1 << PORTA1);\
	PUEA |= (1 << PUEA2);\
	PORTA |= (1 << PORTA1);\
	DDRC |= (1 << PORTC2);\
	PORTC &= ~(1 << PORTC2);\
}

#define IO_setup_ED1_OutPut(){\
	DDRA &= ~(1 << PORTA1);\
	DDRC |= (1 << PORTC2);\
}

#define IO_ED1_OutPut_HIGH(){\
	PORTC  |= ( 1 << PORTC2 );\
}

#define IO_ED1_OutPut_LOW(){\
	PORTC  &= ~(1 << PORTC2);\
}


#define IO_ED1_PullUp_Enable(){\
	PUEA |= (1 << (1));\
}

#define IO_ED1_PullUp_Disable(){\
	PUEA &= ~(1 << PUEA1);\
}

#define	IO_setup_ED2_Input() {\
	DDRA &= ~(1 << PORTA0);\
	DDRC |= (1 << PORTC1);\
	PORTC &= ~(1 << PORTC1);\
}

#define IO_setup_ED2_OutPut() {\
	DDRA &= ~(1 << PORTA0);\
	DDRC |= (1 << PORTC1);\
}


#define IO_ED2_OutPut_HIGH(){\
	PORTC  |= ( 1 << PORTC1 );\
}

#define IO_ED2_OutPut_LOW(){\
	PORTC  &= ~(1 << PORTC1);\
}

#define IO_ED2_PullUp_Enable(){\
	PUEA |= (1 << PUEA0);\
}

#define IO_ED2_PullUp_Disable(){\
	PUEA &= ~(1 << PUEA0);\
}

#endif /* TX006_IO_H_ */