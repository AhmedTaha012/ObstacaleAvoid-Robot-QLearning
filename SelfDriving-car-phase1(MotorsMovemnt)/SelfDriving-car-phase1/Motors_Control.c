/*
 * Motors_Control.c
 *
 * Created: 6/10/2022 2:58:49 PM
 *  Author: DELL
 */ 
#include "Motors_Control.h"
#define Motor_Right_High 0
#define Motor_Right_Low 1
#define Motor_Left_High 2
#define Motor_Left_Low 3
#define Move_port_ddr DDRB //change output port of motor control here 
#define Move_port PORTB
uint8_t outputs[]={0x05,0x0A,0x09,0x06,0x00}; //forward,backward,right,left,off 
		//pins p3 p2 p1 p0
		//0000 0  1  0  1 forward
		//0000 1  0  1  0 backward
		//0000 1  0  0  1 right motor forward left motor reverse ie. left 
		//0000 0  1  1  0 left motor forward right motor reverse ie. right
		//0000 0  0  0  0 stop

void Pwm_Generation_Right_Intilaization(){
	DDRD |= (1<<6);    //Fast PWM output at OC0A pin
	TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//Non-Inverting Fast PWM mode 3 using OCR A unit
	TCCR0B |= (1<<CS00);	//No-Prescalar
}
void Pwm_Generation_Left_Intilaization(){
   DDRD |= (1<<5);    //Fast PWM output at OC0B pin
   TCCR0A |= (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);	//Non-Inverting Fast PWM mode 3 using OCR B unit
   TCCR0B |= (1<<CS00);	//No-Prescalar
}
void Pwm_Generation_Right(uint8_t Speed_precentage){
    OCR0A = Speed_precentage*2.55;	// Duty cycle of 75%
}
void Pwm_Generation_Left(uint8_t Speed_precentage){
	OCR0B = Speed_precentage*2.55;	// Duty cycle of 75%
}
void Move_Intilaization(){
	Move_port_ddr|= ((1<<0)|(1<<1)|(1<<2)|(1<<3)); //use pins 0 to 3 in port as outputs
}

void Move_Car(uint8_t Direction,uint8_t Speed_precentage){
	uint8_t x = Move_port & (0xf0);
	Move_port=outputs[Direction];
                        
	if(Direction==0 || Direction==1){
		Pwm_Generation_Right(Speed_precentage);
		Pwm_Generation_Left(Speed_precentage);
	}
	
	else if(Direction==2){         
		Pwm_Generation_Right(Speed_precentage);
		Pwm_Generation_Left(Speed_precentage);		
	}
	
	else if(Direction==3){
		Pwm_Generation_Right(Speed_precentage);
		Pwm_Generation_Left(Speed_precentage);
	}
	else{Pwm_Generation_Right(0);
		Pwm_Generation_Left(0);}
	
}