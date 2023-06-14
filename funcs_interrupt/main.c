#include "TM4C123GH6PM.h"


#define PortF 5
#define PortA 0
#define PortB 1

enum DIR {IN,OUT};
enum STATE {ON,OFF};


void set_port(int port){
    SYSCTL->RCGCGPIO |= (1 << port);
    while (   !SYSCTL->PRGPIO & (1 << port)   ){ }

}

void set_pin(int pin, enum DIR out_int){
    GPIOF->AFSEL &= ~(1 << pin);
    GPIOF->DEN |= (1 << pin);
    if(out_int == OUT){
        GPIOF->DIR |= (1 << pin);
    }else{
        GPIOF->DIR &= ~(1 << pin);
        GPIOF->PUR |= (1 << pin);
    }

}

void set_portf_data(int pin, enum STATE state){
    if(state == ON){
        GPIOF->DATA |= (1 << pin);
    }else{
        GPIOF->DATA &= ~(1 << pin);
    }
}

void wait(){
    for (int i = 0; i < 0xfffff; i++)
    {
    }
    
}

void white(enum STATE on_off){
    if(on_off == ON){
        set_portf_data(1,ON);
        set_portf_data(2,ON);
        set_portf_data(3,ON);

    }else{
        set_portf_data(1,OFF);
        set_portf_data(2,OFF);
        set_portf_data(3,OFF);
    }
}

void set_interrupt_portf(){
    GPIOF->IS &= ~(1 << 4); // edge detection
    GPIOF->IBE &= ~(1 << 4); // edge detection
    GPIOF->IEV &= ~(1 << 4); // falling edge detection
    GPIOF->IM |= (1 << 4); // interrupt mask

    int reg = 30/32;  // 30 ist PORTF inteerupt nummer
    int bit = 30%32;  // 30 ist PORTF inteerupt nummer
    NVIC->ISER[reg] |= (1 << bit); 
    

}

void init_systick_(){ 

    // (1 / f) * n = t mit f = clk frequency
    float t = 0.050;
    int n = (16e6)*t;

    SysTick->LOAD = n;
    //SysTick->CTRL = (1 << 0) | (1 <<1 ) | (1 << 2);
    SysTick->CTRL = 6;

    
    }


void GPIOPortF_Handler(){
    if( GPIOF->RIS & (1 << 4)){
        GPIOF->ICR |=(1 << 4);
        
        SysTick->CTRL |= 1;
    }




}


void SysTick_Handler(){
    SysTick->CTRL &= ~1;

    if( !(GPIOF->DATA & (1 << 4))){
        GPIOF->DATA ^= (1 << 1);
    }

}


int main(){
    set_port(PortF);
    set_pin(4,IN);
    set_pin(1,OUT);
    set_pin(2,OUT);
    set_pin(3,OUT);
    set_interrupt_portf();
    init_systick_();




    while (1)
    {
        /*set_portf_data(1,ON);
        wait();
        set_portf_data(1,OFF);


        set_portf_data(2,ON);
        wait();
        set_portf_data(2,OFF);


        set_portf_data(3,ON);
        wait();
        set_portf_data(3,OFF);*/
    }
    


    return 0;
}