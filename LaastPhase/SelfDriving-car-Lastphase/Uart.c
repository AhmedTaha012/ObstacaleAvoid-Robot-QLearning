/*
 * Uart.c
 *
 * Created: 6/20/2022 9:37:00 PM
 *  Author: DELL
 */ 
#include "Uart.h"
#define  F_CPU 160000000
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
