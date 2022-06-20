
/*
 * Q-Learning_Algo.c
 *
 * Created: 6/18/2022 1:23:16 AM
 * Author : Ahmed Taha,Ahmed Samer,Noura Medhat,Pavly Safwat,Salma Mohamed
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "Motors_Control.h"
#include <util/delay.h>
#include "Motors_Control.h"
#include "UltraSonic.h"
#include "Uart.h"
#include "Adc.h"

//Initialize the variables 
#define number_states 4          //  number_states
#define  number_of_action 3    //     Actions
float epsilon=0.98;              //train test constant degradation value 
float learning_rate=0.05;       // Learning rate 
float discount_factor=0.5;     // discount 
float  Q_OLD,Q_MAX,Q_NEW;     //  Q values
float Reward_gain;          //   Reward 
int Next_state;             //    Next_State
int action_taken;         //     value to store action taken
int actions[3]={0,1,2}; //0=forward 1=left 2=right 3=Stop  
uint8_t distance_str_1[20];
uint8_t distance_str_2[20];

float Q_Matrix[number_states][number_of_action]={{0.0,0.0,0.0}, //00  empty 00,f 
 	                                              {0.0,0.0,0.0}, //01  // obstacle on right
											      {0.0,0.0,0.0},  //10  // obstacle on left 
												  {0.0,0.0,0.0}};  //11 // both 
													  
													  
float Reward_Martix[number_states][number_of_action]={
	
	                                                  {10.0,-2.0,-3.0},   //00 empty 
												      {-2.0,10.0,-10.0},  //01 on right Purple sees
													  {-2.0,-10.0,10.0},  //10 on left  Brown sees
													  {-10.0,1.0,10.0}   //11 both 
													    
													  };




// functions declaration 
float MAXIMUM(int Next_state);
void seed_init();

void update_epsilon(){
	epsilon=0.98*epsilon;
}

bool Explore_Exploit(){      //returns 1 if explore, 0 if exploit
	double randomno=rand()%100;
	if(randomno/100<epsilon){
		return true;
	}
	else{return false;
	}
}  

int rand_Action(){
	int random_num=rand()%3;//0 1 2 3 4
	return random_num;
} 

int sensor_reading(){
	return get_states_of_ultrasonic();
}


void Update(int S, int NEXT_S, int A, double R, double LEARNING_RATE, double DISCOUNT_FACTOR)
{
  Q_OLD = Q_Matrix[S][A];    //=>0                    
  Q_MAX = MAXIMUM(NEXT_S); //=>0
  Q_NEW = (1-LEARNING_RATE)*Q_OLD + LEARNING_RATE*(R + DISCOUNT_FACTOR*Q_MAX); 
  Q_Matrix[S][A] = Q_NEW;                          
}

float MAXIMUM(int Next_state){
	float max_no=-999;
	int i,index;
	for(i=0;i<number_of_action;i++){
		if(Q_Matrix[Next_state][i]>max_no)
		{
		    max_no=Q_Matrix[Next_state][i];
			index=i;
		}
		
	} 
	float MAXIMUM_VALUE=Q_Matrix[Next_state][index];
	return MAXIMUM_VALUE; // the highest in this state (Next state) 
	
}

float MAX_Action_InState(int state){
	float max=-999;
	int i,index;
	for(i=0;i<number_of_action;i++){
		if(Q_Matrix[state][i]>max)
		{
			max=Q_Matrix[state][i];
			index=i;
		}
		
	}
	
	return index; // the highest in this state (Next state)
	
}






int main(void)
{   
	DDRC=0xff; // Make port Pin 0 in Portc output to connect buzzer to it (We use buzzer to now that robot is starts Testing) 
	Pwm_Generation_Left_Intilaization();  //Initialize the PWM of left motor
	Pwm_Generation_Right_Intilaization(); //Initialize the PWM of right motor 
	ultrasonic_init_1(); // Initialize ultrasonic 1 
	ultrasonic_init_2();// Initialize ultrasonic 2
	Move_Intilaization();// Initialize the motors 
	Serial_monitor_int(); // Initialize the serial monitor 
	sei(); 
	seed_init(); //Initialize 
	int episode_count=100;
    while (1) 
    {  
		  
		 ///////////////////training/////////////////////////////////////////////
 		for(int episodes=0;episodes<episode_count;episodes++) 
 		{   
		   //Print Number Of episode 
			prints_String("------------------------Episode=",28);
			prints_int(episodes,2);
			prints_String("\n",2);
			/// get current state and print
			int state;
			state=sensor_reading(); // 01
			prints_String("State=",6);
			prints_int(state,1);
			prints_String("\n",2);
			//choose Explore or exploit and print the states
 			if(Explore_Exploit()==true){ //true Explore 
				  prints_String("EXPLORE----------",17);
				  prints_String("\n",2);
				  action_taken=rand_Action(); //Choosee Random Action 
				  prints_String("ActionTaken=",12);
				  prints_int(action_taken,1);
				  prints_String("\n",2);
				  }
			 else { //False Exploit
				  prints_String("EXPLOIT----------",17);
				  prints_String("\n",2);
				  action_taken=MAX_Action_InState(state); //Takes Max action In State
				  prints_String("ActionTaken=",12);
				  prints_int(action_taken,1);
				  prints_String("\n",2);
				   }
			//Done Action until state changes 
             do{
				  prints_String("INDOWHILE----------",19);
				  prints_String("\n",2);
	              Action_Done(action_taken);//Done Action until state changes 
				prints_String("ActionTaken=",12);
				prints_int(action_taken,1);
				prints_String("\n",2);
             }while(sensor_reading()==state);
			 //Update new Q ------------------------------------
			 prints_String("OUTWHILE----------",18);
			 prints_String("\n",2);
             Action_Done(3); // Stop car to can read the states
			 prints_String("STOPPPPP----------",18);
			 prints_String("\n",2);
             Next_state=sensor_reading();// Read new state
			 prints_String("NEWState=",9);
			 prints_int(Next_state,1);
			 prints_String("\n",2);
             Reward_gain=Reward_Martix[state][action_taken];//get reward gained of last action 
             Update(state,Next_state,action_taken,Reward_gain,learning_rate,discount_factor);//update Q  
             update_epsilon();//Update epsilon (Decay it)
			 
 		}
		//To show Q Values after training 
		print_q();
		Serial_print('\n');
		///////////////////testing/////////////////////////////////////////////
	while(1){
	     	Serial_print('\n');
		    Serial_print('\n');
			int state;
			state=sensor_reading();
			do{
			    action_taken=MAX_Action_InState(state);
				Action_Done(action_taken);
			}while(sensor_reading()==state);
			Stop();//stop car
        } 		

	}
}

///////////////////Print int value on Serial monitor/////////////////////////
void prints_int(int value,int size )
{   sprintf(distance_str_1, "%d", value);
	for (int i=0;i<size;i++)
	{
		Serial_print(distance_str_1[i]);
		_delay_ms(20);
	}
	//Serial_print('\n');
}


///////////////////Print String value on Serial monitor/////////////////////////
void prints_String(char value[],int size )
{
	for (int i=0;i<size;i++)
	{
		Serial_print(value[i]);
		_delay_ms(20);
	}
	
}


char integers[];
char floats[];
////////////////////////////////////Print Q matrix////////////////////////
void print_q(){
	PORTC=0x01; // for buzzer indication start 
	_delay_ms(1000);
	PORTC=0x00; // for buzzer indication stop
	prints_String("\n",2);
	prints_String("-------------------------------",30);
	prints_String("\n",2);
	prints_String("--TrainingFinsihStartTesting--",30);
	prints_String("\n",2);
	prints_String("-------------------------------",30);
	prints_String("\n",2);
	for(int i=0;i<4;i++){
		prints_String("S",1);
		prints_int(i,1);
		prints_String("--------------------",21);
		prints_String("\n",2);
		for(int j=0;j<3;j++){
			//int temp =(int)Q_Matrix[i][j]*100;
			double2string(Q_Matrix[i][j],integers,floats);
			prints_String(" ",1);
		}
		prints_String("\n",2);
	 }
	}	
	
	
//////////////////Function to do choosen action//////////////////////////////////	
void Action_Done(int action){
	
	if(action==0)
	{
	    Move_Forward();
	}
	else if (action==1)
	{
	   	Move_Left();
	}
	else if (action==2)
	{
		Move_Right();
	}
	else if (action==3)
	{
		Stop();
	}
	
	
	
	
	
}




/////////////////////////////////Print double values on Serial monitor

void double2string (double number, char integers[], char floats[]){
	integers[3] = (  (int)number)%10;
	integers[2] = ( ((int)number)%100 - ((int)number)%10 )/10;
	integers[1] = ( ((int)number)%1000 - ((int)number)%100 )/100;
	integers[0] = ( ((int)number)%10000 - ((int)number)%1000 )/1000;
	number -= (int)number;
	number = number* 10000;

	floats[3] = (  (int)number)%10;
	floats[2] = ( ((int)number)%100 - ((int)number)%10 )/10;
	floats[1] = ( ((int)number)%1000 - ((int)number)%100 )/100;
	floats[0] = ( ((int)number)%10000 - ((int)number)%1000 )/1000;
	if (number<0){prints_String("-",1);}
	for (int i=0;i<4;i++)
	{
		prints_int(integers[i],1);
	}
	prints_String(".",1);
	for (int i=0;i<4;i++)
	{
		prints_int(floats[i],1);
	}
	
}



