#ifndef __TOOLS__
#define __TOOLS__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TM4C123GH6PM.h"
#include <stdarg.h>

#define PORT_A 0;
#define PORT_B 1;
#define PORT_C 2;
#define PORT_D 3;
#define PORT_E 4;
#define PORT_F 5;




enum io {INPUT,OUTPUT};
enum level {LOW,HIGH};
enum clock {SYS_CLOCK,PRECISION_CLOCK};

void init_gpio_port(unsigned port_num,...);
void init_systick(unsigned time_in_ms, enum clock clk);
void init_pin(GPIOA_Type * port,int pin_num,...);
void set_pin_data(GPIOA_Type * port,int pin_num,...);
void init_adc_analog_inputs(unsigned pin_num,...);
void init_uart0(unsigned Baudrate);
void send_char(char c);
char get_char();
void send_string(char * str);
void init_adc0(unsigned samples,...);
void set_interrupt(GPIOA_Type * port, unsigned pin, unsigned irqn);


#endif //__TOOLS__