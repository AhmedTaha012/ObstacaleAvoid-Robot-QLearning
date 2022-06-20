/*
 * Uart.h
 *
 * Created: 6/20/2022 9:36:44 PM
 *  Author: DELL
 */ 


#ifndef UART_H_
#define UART_H_
#include <avr/io.h>
#include <stdbool.h>

void Serial_monitor_int();
void Serial_print(uint8_t value);

#endif /* UART_H_ */