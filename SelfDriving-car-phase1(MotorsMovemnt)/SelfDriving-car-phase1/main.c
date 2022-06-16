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
    
    Pwm_Generation_Left_Intilaization();
    Pwm_Generation_Right_Intilaization();
    Move_Intilaization();
    while (1) 
    {
// 		for(int i=0;i<5;i++)
// 		{
// 			Move_Car(i,50);
// 			_delay_ms(1000);
// 		}
		Move_Car(3,50);
    }
}
