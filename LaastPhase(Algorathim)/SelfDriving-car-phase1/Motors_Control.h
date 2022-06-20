/*
 * Motors_Control.h
 *
 * Created: 6/10/2022 2:57:37 PM
 *  Author: DELL
 */ 


#ifndef MOTORS_CONTROL_H_
#define MOTORS_CONTROL_H_
#include <avr/io.h>
void Move_Right();
void Move_Left();
void Move_Forward();
void Move_Backward();
void Stop();
void Pwm_Generation_Right(uint8_t Speed_precentage); //OC0A
void Pwm_Generation_Left(uint8_t Speed_precentage); // OC0B
void Pwm_Generation_Right_Intilaization();
void Pwm_Generation_Left_Intilaization();
void Move_Intilaization();
void Move_Car(uint8_t Direction,uint8_t Speed_precentage);
#endif /* MOTORS_CONTROL_H_ */