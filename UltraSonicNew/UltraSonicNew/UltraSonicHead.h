/*
 * UltraSonicHead.h
 *
 * Created: 6/19/2022 12:30:16 AM
 *  Author: DELL
 */ 


#ifndef ULTRASONICHEAD_H_
#define ULTRASONICHEAD_H_
#include<avr/io.h>
#include <avr/interrupt.h>
#include<string.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <util/delay.h>



#define   TRIGER_DDR    DDRD
#define   ECHO_DDR      DDRD
#define   TRIGER_PORT   PORTD
#define   ECHO_PULLUP   PORTD
#define   TRIGER        2
#define   ECHO          7


void ultrasonic_init(void);
void enable_ex_interrupt(void);
void ultrasonic_triger(void);





#endif /* ULTRASONICHEAD_H_ */