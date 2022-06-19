/*
 * Ultrasonic.c
 *
 * Created: 6/19/2022 12:26:53 AM
 *  Author: DELL
 */ 
#include "UltraSonicHead.h"
uint8_t sensor_working=0;
uint8_t rising_edge=0;
uint32_t timer_counter=0;
uint32_t distance;
uint8_t distance_str[10];

#define FAST_PWM						        (1<<3)|(1<<6)
#define NON_INVERT						      (1<<5)
#define PRESCLR1_VALUE 		            0x01
#define PRESCLR8_VALUE 		            0x02
#define PRESCLR64_VALUE 	            0x03
#define PRESCLR256_VALUE 	            0x04
#define PRESCLR1024_VALUE 	          0x05
#define DISABLE_MODULE_VALUE 		      0x00
/* Timer DDR */
#define TIMER0_DDR						        DDRB
#define TIMER2_DDR					         	DDRD
/* to put in the PWM_init function */
#define TIMER_0                         0
#define TIMER_2                         2
/* Out compare pin */
#define OC0_OUTPUT_SETTER               3
#define OC2_OUTPUT_SETTER               7
#define ZER0_INITIALIZER                0x00
/* Max counts of timer0 is 2^8=255 */
#define TIMER_MAX_VALUE                 255
/* max Percentage Value (100%) */

void timer0_init(void)
{
	/* Disable Timer 0 */
	TCCR0A = DISABLE_MODULE_VALUE;
	/* Setting pre scaler */
	TCCR0B = (PRESCLR1_VALUE);
	/* Initializing the timer with zero */
	TCNT0 = ZER0_INITIALIZER;
	/* Timer overflow interrupt enable*/
	TIMSK0 |=(1<<TOIE0);

	return;
}




void ultrasonic_init(void){

	TRIGER_DDR|=(1<<TRIGER);
	ECHO_DDR&=~(1<<ECHO);
	ECHO_PULLUP|=(1<<ECHO);
	enable_ex_interrupt();
	timer0_init();
	return;
}

void enable_ex_interrupt(void){

	MCUCR |= (1<<ISC10);		// Trigger INT1 on any logic change.
	EIMSK |= (1<<INT1);			// Enable INT1 interrupts.

	return;
}

void ultra_triger(void){
	if(!sensor_working){
		TRIGER_PORT|=(1<<TRIGER);
		_delay_us(15);
		TRIGER_PORT&=~(1<<TRIGER);
		sensor_working=1;
	}
}

ISR(INT1_vect){
	if(sensor_working==1){
		if(rising_edge==0){
			TCNT0=0x00;
			rising_edge=1;
			timer_counter=0;
		}
		else{
			distance=(timer_counter*256+TCNT0)/932.8;
			lcd_goto_xy(1,0);
			itoa(distance,distance_str,10);
			strcat(distance_str, " cm ");
			lcd_write_word(distance_str);
			_delay_ms(40);
			timer_counter=0;
			rising_edge=0;
		}
	}}

	ISR(TIMER0_OVF_vect){
		timer_counter++;
		if(timer_counter >730){
			TCNT0=0x00;
			sensor_working=0;
			rising_edge=0;
			timer_counter=0;
		}
	}