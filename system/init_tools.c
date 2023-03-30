#include "init_tools.h"



void init_gpio_port(unsigned port_num,...)
{
    va_list args;
    va_start(args,port_num);
    for (int i = 0; i < port_num; i++)
    {

        unsigned port = va_arg(args,unsigned);
        SYSCTL->RCGCGPIO |= (1 << port);
        while (!(SYSCTL->PRGPIO & (1 << port)))
        {
        }
        
    }
    
    va_end(args);
}


void init_systick(unsigned time_in_ms, enum clock clk)
{
    unsigned ticks = 0;
    switch (clk)
    {
        case SYS_CLOCK: {ticks = (16e6 * time_in_ms * 10e3); SysTick->LOAD = ticks; SysTick->CTRL &= ~0x7  ;SysTick->CTRL |= 0x7; break;}
        case PRECISION_CLOCK:{ticks = (4e6 * time_in_ms * 10e3); SysTick->LOAD = ticks; SysTick->CTRL &= ~0x7  ;SysTick->CTRL |= 0x3; break;}
    }
}


void init_pin(GPIOA_Type * port,int pin_num,...)
{
    unsigned pins[pin_num];
    unsigned pins_states[pin_num];
    va_list args;
    va_start(args,pin_num);

    for (int i = 0; i < (pin_num * 2); i++)
    {
        unsigned arg = va_arg(args,unsigned);
        if(i < pin_num )
        {
            pins[i] = arg;
        }
        else
        {
            pins_states[i % pin_num] = arg;
        }
    }

    for (int i = 0; i < pin_num; i++)
    {
        port->AFSEL &= ~(1 << pins[i]);
        if(pins_states[i] == 0)
        {
            port->DIR &= ~(1 << pins[i]);
            port->PUR |= (1 << pins[i]);

        }else{
            port->DIR |= (1 << pins[i]);
        }
        port->DEN |= (1 << pins[i]);
    }
    

    va_end(args);
    
}

void set_pin_data(GPIOA_Type * port,int pin_num,...)
{
    unsigned pins[pin_num];
    unsigned pins_states[pin_num];
    va_list args;
    va_start(args,pin_num);

    for (int i = 0; i < (pin_num * 2); i++)
    {
        unsigned arg = va_arg(args,unsigned);
        if(i < pin_num )
        {
            pins[i] = arg;
        }
        else
        {
            pins_states[i % pin_num] = arg;
        }
    }

    for (int i = 0; i < pin_num; i++)
    {
        if(pins_states[i] == 0)
        {
            port->DATA &= ~(1 << pins[i]);

        }else{
            port->DATA |= (1 << pins[i]);
        }
        
    }
    

    va_end(args);

}

void init_adc_analog_inputs(unsigned pin_num,...)
{
    va_list args;
    va_start(args,pin_num);
    for (int i = 0; i < pin_num; i++)
    {

        unsigned ain = va_arg(args,unsigned);
        switch (ain)
        {
            case 0 : { GPIOE->AFSEL |= (1 << 3);GPIOE->AMSEL |= (1 << 3);GPIOE->DEN &= ~(1 << 3); ;break;}
            case 1 : { GPIOE->AFSEL |= (1 << 2);GPIOE->AMSEL |= (1 << 2);GPIOE->DEN &= ~(1 << 2); ;break;}
            case 2 : { GPIOE->AFSEL |= (1 << 1);GPIOE->AMSEL |= (1 << 1);GPIOE->DEN &= ~(1 << 1); ;break;}
            case 3 : { GPIOE->AFSEL |= (1 << 0);GPIOE->AMSEL |= (1 << 0);GPIOE->DEN &= ~(1 << 0); ;break;}
            
            case 4 : { GPIOD->AFSEL |= (1 << 3);GPIOD->AMSEL |= (1 << 3);GPIOD->DEN &= ~(1 << 3); ;break;}
            case 5 : { GPIOD->AFSEL |= (1 << 2);GPIOD->AMSEL |= (1 << 2);GPIOD->DEN &= ~(1 << 2); ;break;}
            case 6 : { GPIOD->AFSEL |= (1 << 1);GPIOD->AMSEL |= (1 << 1);GPIOD->DEN &= ~(1 << 1); ;break;}
            case 7 : { GPIOD->AFSEL |= (1 << 0);GPIOD->AMSEL |= (1 << 0);GPIOD->DEN &= ~(1 << 0); ;break;}

           
            case 8 : { GPIOE->AFSEL |= (1 << 5);GPIOE->AMSEL |= (1 << 5);GPIOE->DEN &= ~(1 << 5); ;break;}
            case 9 : { GPIOE->AFSEL |= (1 << 4);GPIOE->AMSEL |= (1 << 4);GPIOE->DEN &= ~(1 << 4); ;break;}
            case 10 : { GPIOB->AFSEL |= (1 << 4);GPIOB->AMSEL |= (1 << 4);GPIOB->DEN &= ~(1 << 4); ;break;}
            case 11 : { GPIOB->AFSEL |= (1 << 5);GPIOB->AMSEL |= (1 << 5);GPIOB->DEN &= ~(1 << 5); ;break;}
        }
        
    }
    
    va_end(args);
}


void init_uart0(unsigned Baudrate)
{
    SYSCTL->RCGCUART |= (1 << 0);
    while (!(SYSCTL->PRUART & (1 << 0)))
        {
        }
    
    GPIOA->AFSEL |= 0x3;
    GPIOA->PCTL |= 1 | (1 << 4);
    GPIOA->DEN |= 0x3;

    int ibrd = (int)( 16e6 /(16 * Baudrate));
    int fbrd = (int) (((16e6 /(16 * Baudrate)) - ibrd) * 64 + 0.5); 

    UART0->CTL &= ~(1 << 0);
    UART0->IBRD = ibrd;
    UART0->FBRD = fbrd;
    UART0->LCRH = (3 < 5);
    UART0->CTL |= 1;
}

void send_char(char c)
{
    while (UART0->FR & (1 << 5))
    {
    }
    UART0->DR = c;
    
}

char get_char()
{
    while (UART0->FR & (1 << 4))
    {
    }
    return UART0->DR ;
    
}

void send_string(char * str)
{
    for (char * i = str; *i != 0; i++)
    {
        send_char(*i);
    }
    
}

void init_adc0(unsigned samples,...)
{
    ADC0->ACTSS &= ~(1 << 0);
    va_list args;
    va_start(args,samples);
    unsigned stelle = 0;
    for (int i = 0; i < samples; i++)
    {
        unsigned ain = va_arg(args,unsigned);
        ADC0->SSMUX0 |= (ain << stelle);
        stelle +=4;
    }
    stelle -=4;

    ADC0->SSCTL0 |= (3 << (stelle+1));
    ADC0->EMUX &= ~0xf;
    ADC0->IM |= (1 << 0);
    NVIC->ISER[0] |= (1 << 14);
    ADC0->ACTSS |= (1 << 0);
    
    va_end(args);
    
}

void set_interrupt(GPIOA_Type * port, unsigned pin, unsigned irqn)
{
    port->IS &=(1 << pin);
    port->IBE &=(1 << pin);
    port->IEV &=(1 << pin);
    port->IM |=(1 << pin);
    unsigned reg = irqn / 32;
    unsigned bit = irqn % 32;
    NVIC->ISER[reg] |= (1 << bit);
}