/*
 * UltraSonic.h
 *
 * Created: 6/19/2022 7:35:07 PM
 *  Author: DELL
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include <avr/interrupt.h>
#include <stdio.h>
#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define RS PB0				/* Define Register Select pin */
#define EN PB1 				/* Define Enable signal pin */
#define  F_CPU 16000000UL



#define PRESCLR1_VALUE 		            0x01
#define DISABLE_MODULE_VALUE 		      0x00
#define   TRIGER_DDR_1    DDRB
#define   ECHO_DDR_1     DDRD
#define   TRIGER_PORT_1   PORTB
#define   ECHO_PULLUP_1   PORTD
#define   TRIGER_DDR_2    DDRB
#define   ECHO_DDR_2     DDRD
#define   TRIGER_PORT_2   PORTB
#define   ECHO_PULLUP_2   PORTD
#define   TRIGER1        5
#define   ECHO1          2
#define   TRIGER2        4
#define   ECHO2          3
void timer0_init(void);
void timer2_init(void);
void ultrasonic_init_1(void);
void ultrasonic_init_2(void);
void ultra_triger_1(void);
void ultra_triger_2(void);
int read_ultra_1();
int read_ultra_2();
int get_states_of_ultrasonic();



#endif /* ULTRASONIC_H_ */