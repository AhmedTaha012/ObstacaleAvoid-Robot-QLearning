/*
 * SelfDriving-car-phase1.c
 *
 * Created: 6/10/2022 2:33:55 PM
 * Author : DELL
 */ 


#include "Motors_Control.h"
#include <util/delay.h>			/* Include Delay header file */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define RS PB0				/* Define Register Select pin */
#define EN PB1 				/* Define Enable signal pin */
#define  F_CPU 16000000UL
uint8_t sensor_working_1=0;
uint8_t sensor_working_2=0;
uint8_t rising_edge_1=0;
uint8_t rising_edge_2=0;
uint32_t timer_counter_1=0;
uint32_t timer_counter_2=0;
volatile uint32_t distance_1;
volatile uint32_t distance_2;
uint8_t distance_str_1[20];
uint8_t distance_str_2[20];
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

#define BAUD 9600
#define BRC ((F_CPU/16/BAUD)-1)
void Serial_monitor_int()
{
	UBRR0H=(BRC>>8);
	UBRR0L=BRC;
	UCSR0B=(1<<TXEN0);
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);

}
void Serial_print(uint8_t value){
	UDR0=value;
}



int main(void)
{
    
   Pwm_Generation_Left_Intilaization();
    Pwm_Generation_Right_Intilaization();
    Move_Intilaization();
	//Serial_monitor_int();
	//ultrasonic_init_1();
	//ultrasonic_init_2();
	//DDRB=0xff;
	
    while (1) 
    {
		
		Move_Car(2,40);
		//_delay_us(1000);
		//Move_Car(1,10);
		//_delay_ms(60);
		//PORTB=0x05;
		
		
    }
}
void timer0_init(void)
{
	/* Disable Timer 0 */
	TCCR0A = DISABLE_MODULE_VALUE;
	/* Setting pre scaler */
	TCCR0B = (PRESCLR1_VALUE);
	/* Initializing the timer with zero */
	TCNT0 = 0x00;
	/* Timer overflow interrupt enable*/
	TIMSK0 |=(1<<TOIE0);
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
			TCNT0=0x00;
			rising_edge_1=1;
			timer_counter_1=0;
		}
		else{
			
			distance_1=(timer_counter_1*256+TCNT0)/932.8;
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

ISR(TIMER0_OVF_vect){
	timer_counter_1++;
	if(timer_counter_1 >730){
		TCNT0=0x00;
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
	
	if(read_ultra_1()>20 && read_ultra_2()>20){
		return 0;
	}
	else if (read_ultra_1()>20 && read_ultra_2()<20){
		return 1;
	}
	else if (read_ultra_1()<20 && read_ultra_2()>20){
		return 2;
	}
	else if (read_ultra_1()<20 && read_ultra_2()<20){
		return 3;
	}
	else if (read_ultra_1()<15 && read_ultra_2()<15){
		return 4;
	}
	
	

	




}