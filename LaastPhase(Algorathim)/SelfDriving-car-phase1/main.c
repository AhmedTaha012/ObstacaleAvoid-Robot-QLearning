/*
 * SelfDriving-car-phase1.c
 *
 * Created: 6/10/2022 2:33:55 PM
 * Author : DELL
 */ 












//int main(void)
//{ 
	//
    //
    //Pwm_Generation_Left_Intilaization();
    //Pwm_Generation_Right_Intilaization();
	//ultrasonic_init_1();
    //ultrasonic_init_2();
    //Move_Intilaization();
	//Serial_monitor_int();
	//sei();
	//Move_Forward();
    //Move_Forward();
	//Move_Forward();
	//Move_Left();
    //
    //while (1) 
    //{ 
	 //sprintf(distance_str_1, "%d", get_states_of_ultrasonic());
	    //for(int i=0;i<2;i++)
	    //{Serial_print(distance_str_1[i]);
		   //_delay_ms(100);
		    //Serial_print('\n');
	    //}
	//}
	  //
	 //
	  //
	  //
	  //
	  //
    //
//}






/*
 * Q-Learning_Algo.c
 *
 * Created: 6/18/2022 1:23:16 AM
 * Author : DELL
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "Motors_Control.h"
#include <util/delay.h>
#include "Motors_Control.h"
#include "UltraSonic.h"
uint8_t distance_str_1[20];
uint8_t distance_str_2[20];
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
float Q_Matrix[number_states][number_of_action]={{0.0,0.0,0.0}, //00  empty 00,f 
 	                                              {0.0,0.0,0.0}, //01  // obstacle on right
											      {0.0,0.0,0.0},  //10  // obstacle on left 
												  {0.0,0.0,0.0}};  //11 // both 
													  
													  
float Reward_Martix[number_states][number_of_action]={
	
	                                                  {10.0,-2.0,-3.0},   //00 empty 
												      {-2.0,10.0,-10.0},  //01 on right Purple sees
													  {-2.0,-10.0,10.0},  //10 on left  Brown sees
													  {-10.0,1.0,10.0}  //11 both 
													    
													  };

float MAXIMUM(int Next_state);
void seed_init();


// functions declaration 
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
void adc_init(void){
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));   // 16Mhz/128 = 125Khz the ADC reference clock
	ADMUX |= (1<<REFS0);                            // Voltage reference from Avcc (5v)
	ADCSRA |= (1<<ADEN);                            // Turn on ADC
	ADCSRA |= (1<<ADSC);                            // Do an initial conversion because this one is the slowest and to ensure that everything is up and running
}
uint16_t read_adc(uint8_t channel){
	ADMUX &= 0xF0;                            // Clear the older channel that was read
	ADMUX |= channel;                            // Defines the new ADC channel to be read
	ADCSRA |= (1<<ADSC);                            // Starts a new conversion
	while(ADCSRA & (1<<ADSC));                        // Wait until the conversion is done
	return ADCW;                                // Returns the ADC value of the chosen channel
}
void seed_init()
{
	uint16_t u_rand_val = 0;
	uint16_t u_seed_rand_val = 0;
	adc_init();
	//Note we're assuming the channel that you are reading from is FLOATING or hooked up to something very noisy.
	//Gather bits from the adc, pushing them into your pseudorandom seed.
	for(uint8_t i=0; i<16; i++){
		u_seed_rand_val = u_seed_rand_val<<1 | (read_adc(i)&0b1);
	}
	srand (u_seed_rand_val);

}

void prints_float(double value,int size )
{   sprintf(distance_str_1, "%f", value);
	for (int i=0;i<size;i++)
	{
		Serial_print(distance_str_1[i]);
		_delay_ms(20);
	}
	Serial_print(' ');
}
char str[5]="ahmed";
void prints_int(int value,int size )
{   sprintf(distance_str_1, "%d", value);
	for (int i=0;i<size;i++)
	{
	Serial_print(distance_str_1[i]);
	_delay_ms(20);
	}
	//Serial_print('\n');
}
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






int main(void)
{   DDRC=0xff;
	Pwm_Generation_Left_Intilaization();
	Pwm_Generation_Right_Intilaization();
	ultrasonic_init_1();
	ultrasonic_init_2();
	Move_Intilaization();
	Serial_monitor_int();
	sei();
	seed_init();
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
 			if(Explore_Exploit()==true){
				  prints_String("EXPLORE----------",17);
				  prints_String("\n",2);
				  action_taken=rand_Action();
				  prints_String("ActionTaken=",12);
				  prints_int(action_taken,1);
				  prints_String("\n",2);
				  }
			 else { 
				  prints_String("EXPLOIT----------",17);
				  prints_String("\n",2);
				  action_taken=rand_Action();
				  action_taken=MAX_Action_InState(state);
				  prints_String("ActionTaken=",12);
				  prints_int(action_taken,1);
				  prints_String("\n",2);
				   }
             do{
				  prints_String("INWHILE----------",17);
				  prints_String("\n",2);
	              Action_Done(action_taken);
				prints_String("ActionTaken=",12);
				prints_int(action_taken,1);
				prints_String("\n",2);
             }while(sensor_reading()==state);
			 prints_String("OUTWHILE----------",18);
			 prints_String("\n",2);
             Action_Done(4);
			 prints_String("STOPPPPP----------",18);
			 prints_String("\n",2);
             Next_state=sensor_reading();// 11
			 prints_String("NEWState=",9);
			 prints_int(Next_state,1);
			 prints_String("\n",2);
             Reward_gain=Reward_Martix[state][action_taken];//00 f r=10
             Update(state,Next_state,action_taken,Reward_gain,learning_rate,discount_factor);
             update_epsilon();
			 
 		}
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









