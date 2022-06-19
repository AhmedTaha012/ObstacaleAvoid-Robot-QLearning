/*
 * Motors_Control.c
 *
 * Created: 6/10/2022 2:58:49 PM
 *  Author: DELL
 */ 
#define Motor_Right_High 0
#define Motor_Right_Low 1
#define Motor_Left_High 2
#define Motor_Left_Low 3


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