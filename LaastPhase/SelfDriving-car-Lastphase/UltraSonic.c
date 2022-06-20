/*
 * UltraSonic.c
 *
 * Created: 6/19/2022 7:35:26 PM
 *  Author: DELL
 */ 
#include "UltraSonic.h"
#include <util/delay.h>
#include "Motors_Control.h"
#include <avr/io.h>
#include <stdbool.h>
#include "Motors_Control.h"
uint8_t sensor_working_1=0;
uint8_t sensor_working_2=0;
uint8_t rising_edge_1=0;
uint8_t rising_edge_2=0;
uint32_t timer_counter_1=0;
uint32_t timer_counter_2=0;
volatile uint32_t distance_1;
volatile uint32_t distance_2;

void timer0_init(void)
{
	/* Disable Timer 0 */
	TCCR1A = DISABLE_MODULE_VALUE;
	/* Setting pre scaler */
	TCCR1B = (PRESCLR1_VALUE);
	/* Initializing the timer with zero */
	TCNT1 = 0x00;
	/* Timer overflow interrupt enable*/
	TIMSK1 |=(1<<TOIE1);
	return;
}

void timer2_init(void)
{
	/* Disable Timer 0 */
	TCCR2A = DISABLE_MODULE_VALUE;
	/* Setting pre scaler */
	TCCR2B = (PRESCLR1_VALUE);
	/* Initializing the timer with zero */
	TCNT2 = 0x00;
	/* Timer overflow interrupt enable*/
	TIMSK2 |=(1<<TOIE2);
	return;
}


void ultrasonic_init_1(void){

	TRIGER_DDR_1|=(1<<TRIGER1);
	ECHO_DDR_1&=~(1<<ECHO1);
	ECHO_PULLUP_1|=(1<<ECHO1);
	EICRA |= (1<<ISC00);		// Trigger INT1,INT0 on any logic change.
	EIMSK |= (1<<INT0);			// Enable INT1,INT0 interrupts.
	timer0_init();
	return;
}

void ultrasonic_init_2(void){

	TRIGER_DDR_2|=(1<<TRIGER2);
	ECHO_DDR_2&=~(1<<ECHO2);
	ECHO_PULLUP_2|=(1<<ECHO2);
	EICRA |= (1<<ISC10);		// Trigger INT1,INT0 on any logic change.
	EIMSK |= (1<<INT1);			// Enable INT1,INT0 interrupts.
	timer2_init();
	return;
}


void ultra_triger_1(void){
	if(!sensor_working_1){
		TRIGER_PORT_1|=(1<<TRIGER1);
		_delay_us(15);
		TRIGER_PORT_1&=~(1<<TRIGER1);
		sensor_working_1=1;
	}
}
void ultra_triger_2(void){
	if(!sensor_working_2){
		TRIGER_PORT_2|=(1<<TRIGER2);
		_delay_us(15);
		TRIGER_PORT_2&=~(1<<TRIGER2);
		sensor_working_2=1;
	}
}

ISR(INT0_vect){
	
	if(sensor_working_1==1){

		if(rising_edge_1==0){
			
			TCNT1=0x00;
			rising_edge_1=1;
			timer_counter_1=0;
		}
		else{
			
			distance_1=(timer_counter_1*65536+TCNT1)/932.8;
			timer_counter_1=0;
			rising_edge_1=0;
		}
	}
	
}

ISR(INT1_vect){
	
	if(sensor_working_2==1){
		
		if(rising_edge_2==0){
			
			TCNT2=0x00;
			rising_edge_2=1;
			timer_counter_2=0;
		}
		else{
			
			distance_2=(timer_counter_2*256+TCNT2)/932.8;
			timer_counter_2=0;
			rising_edge_2=0;
		}
	}
	
}

ISR(TIMER1_OVF_vect){
	timer_counter_1++;
	if(timer_counter_1 >730){
		TCNT1=0x00;
		sensor_working_1=0;
		rising_edge_1=0;
		timer_counter_1=0;
	}
}

ISR(TIMER2_OVF_vect){
	timer_counter_2++;
	if(timer_counter_2 >730){
		TCNT2=0x00;
		sensor_working_2=0;
		rising_edge_2=0;
		timer_counter_2=0;
	}
	
}

int read_ultra_1(){
	
	ultra_triger_1();
	_delay_us(15);
	return distance_1;
	
}

int read_ultra_2(){
	
	ultra_triger_2();
	_delay_us(15);
	return distance_2;
	
}
int get_states_of_ultrasonic(){
	
	if(read_ultra_1()>20 && read_ultra_2()>20){ // nothing front
		return 0;
	}
	else if (read_ultra_1()>20 && read_ultra_2()<20){ //nothing in right
		return 1;
	}
	else if (read_ultra_1()<20 && read_ultra_2()>20){ //nothing in left 
		return 2;
	}
	else if (read_ultra_1()<20 && read_ultra_2()<20){ // in bad situation
		return 3;
	}
	else if (read_ultra_1()<10 || read_ultra_2()<10){
		return 4;
	}
}
	
