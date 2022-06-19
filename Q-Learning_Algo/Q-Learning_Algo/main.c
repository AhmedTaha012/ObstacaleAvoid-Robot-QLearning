/*
 * Q-Learning_Algo.c
 *
 * Created: 6/18/2022 1:23:16 AM
 * Author : DELL
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "Motors_Control.h"
#include "QAlgorathim.h"
//Initialize the variables 

double epsilon=0.98;              //train test constant degradation value 
double learning_rate=0.01;       // Learning rate 
double discount_factor=0.5;     // discount 
double  Q_OLD,Q_MAX,Q_NEW;     //  Q values
int number_states=4;          //  number_states
double Reward_gain;          //   Reward 
int Next_state;             //    Next_State
int number_of_action=5;    //     Actions
int action_taken;         //     value to store action taken
int actions[4]={0,1,2,3,4}; //0=forward 1 backward 2=left 3=right 4=Stop  
	
double Q_Matrix[number_states][number_of_action]={{0,0,0,0,0}, //00  empty 00,f 
 	                                              {0,0,0,0,0}, //01  // obstacle on right
											      {0,0,0,0,0},  //10  // obstacle on left 
												  {0,0,0,0,0}};  //11 // both 
													  
													  
double Reward_Martix[number_states][number_of_action]={
	
	                                                  {10,-2,-1,-1,-10},   //00 empty 
												      {-2,-1,10,-10,-1},  //01 on right
													  {-2,-1,-10,10,-1},  //10 on left 
													  {-10,10,-1,-1,-2}  //11 both 
													    
													  };





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
	int random_num=rand()%4;//0 1 2 3 4
	return random_num;
} 
int sensor_reading(){
	//output state no. 0->3
}


void Update(int S, int NEXT_S, int A, double R, double LEARNING_RATE, double DISCOUNT_FACTOR)
{
  Q_OLD = Q_Matrix[S][A];    //=>0                    
  Q_MAX = MAX(NEXT_S); //=>0
  Q_NEW = (1-LEARNING_RATE)*Q_OLD + LEARNING_RATE*(R + DISCOUNT_FACTOR*Q_MAX); 
  Q_Matrix[S][A] = Q_NEW;                          
}

double MAX(int Next_state){
	double max=-999;
	int i,index;
	for(i=0;i<number_of_action;i++){
		if(Q_Matrix[Next_state][i]>max)
		{
		    max=Q_Matrix[Next_state][i];
			index=i;
		}
		
	} 
	
	return Q_Matrix[Next_state][index]; // the highest in this state (Next state) 
	
}

double MAX_Action_InState(int state){
	double max=-999;
	int i,index;
	for(i=0;i<number_of_action;i++){
		if(Q_Matrix[Next_state][i]>max)
		{
			max=Q_Matrix[Next_state][i];
			index=i;
		}
		
	}
	
	return index; // the highest in this state (Next state)
	
}



int main(void)
{
    while (1) 
    {
		seed_init();
 		int episode_count=10;
		 ///////////////////Training/////////////////////////////////////////////
 		for(int episodes=0;episodes<episode_count;episodes++) 
 		{
			int state;
			state=sensor_reading(); // 00
 			if(Explore_Exploit()==true){  //true= explore,false=exploit
				 action_taken=rand_Action(); }
			 else if(Explore_Exploit()==false){  action_taken=MAX_Action_InState(state); }
             do{
	             Move_Car(action_taken,50);
             }while(sensor_reading()==state);
             Move_Car(4,50);//stop car
             Next_state=sensor_reading();// 11
             Reward_gain=Reward_Martix[state][action_taken];//00 f r=10
             Update(state,Next_state,action_taken,Reward_gain,learning_rate,discount_factor);
             update_epsilon();
 		}
		///////////////////Testing/////////////////////////////////////////////
		while(1){
			int state;
			state=sensor_reading();
			do{
			action_taken=MAX_Action_InState(state);
			}while(sensor_reading()==state);
			Move_Car(4,50);//stop car
        }
		
		
}

