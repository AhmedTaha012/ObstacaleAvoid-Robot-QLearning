/*
 * SelfDriving-car-phase1.c
 *
 * Created: 6/10/2022 2:33:55 PM
 * Author : DELL
 */ 

#include <util/delay.h>
#include "Motors_Control.h"
int main(void)
{
    DDRB=0xff;
    //Pwm_Generation_Left_Intilaization();
    //Pwm_Generation_Right_Intilaization();
    //Move_Intilaization();
    while (1) 
    {
		PORTB=0x05; //move forward 
		_delay_ms(3000);
		PORTB=0x0A; // move backward
		_delay_ms(3000);
    }
}
