/*
 * LCDCONF.h
 *
 * Created: 6/19/2022 12:35:38 AM
 *  Author: DELL
 */ 


#ifndef LCDCONF_H_
#define LCDCONF_H_
//LCD DATA AND CONTROL PORTS
#define   DATA_BUS 	    	 PORTB
#define   CTL_BUS		     PORTB
#define   DATA_DDR	    	 DDRB
#define   CTL_DDR		     DDRB

//LCD DATA PINS
#define   LCD_D4			   3
#define   LCD_D5			   4
#define   LCD_D6			   5
#define   LCD_D7			   6

// LCD CONTROL PINS
#define   LCD_EN			   2
#define	  LCD_RW			   1
#define	  LCD_RS			   0




#endif /* LCDCONF_H_ */