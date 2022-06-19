/*
 * UltraSonicNew.c
 *
 * Created: 6/19/2022 12:25:45 AM
 * Author : DELL
 */ 
#include <util/delay.h>			/* Include Delay header file */
#include <avr/io.h>	
#include <avr/interrupt.h>
#include <stdio.h>
#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define RS PB0				/* Define Register Select pin */
#define EN PB1 				/* Define Enable signal pin */

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
#define   TRIGER_DDR_1    DDRD
#define   ECHO_DDR_1     DDRD
#define   TRIGER_PORT_1   PORTD
#define   ECHO_PULLUP_1   PORTD
#define   TRIGER_DDR_2    DDRD
#define   ECHO_DDR_2     DDRD
#define   TRIGER_PORT_2   PORTD
#define   ECHO_PULLUP_2   PORTD
#define   TRIGER1        7
#define   ECHO1          2
#define   TRIGER2        6
#define   ECHO2          3











int main(void)
{
   
   LCD_Init();			/* Initialization of LCD*/
   ultrasonic_init_1();
   ultrasonic_init_2();
   sei();
   while(1){
	   ultra_triger_1();
	   _delay_us(15);
	   sprintf(distance_str_1, "%d", distance_1);
	   LCD_String_xy(0,0,distance_str_1);
	   _delay_ms(10);
	    ultra_triger_2();
	    _delay_us(15);
	    sprintf(distance_str_2, "%d", distance_2);
	    LCD_String_xy(1,1,distance_str_2);
	    _delay_ms(10);
	   
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

	
















void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_Port |= (1<<EN);		/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_us(200);
	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port |= (1<<RS);		/* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Dir = 0xFF;			/* Make LCD port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command(0x02);		/* send for 4 bit initialization of LCD  */
	LCD_Command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0x0c);              /* Display on cursor off*/
	LCD_Command(0x06);              /* Increment cursor (shift cursor to right)*/
	LCD_Command(0x01);              /* Clear display screen*/
	_delay_ms(2);
}


void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
}