#include "TM4C123GH6PM.h"


void uart_init(){
    SYSCTL->RCGCUART |=(1 << 0);
    while( ! (SYSCTL->PRUART & (1 << 0))){}

    int ibrd = 16e6 / (16 * 9600);
    int fbrd = (16e6 / (16 * 9600) - ibrd) * 64 + 0.5;

    UART0->CTL &= ~(1 << 0);

    UART0->IBRD = ibrd;
    UART0->FBRD = fbrd;
    UART0->LCRH |= (7 << 4);
    UART0->LCRH &= ~(1<< 1);
    
    UART0->CTL |= (1 << 0);



}

void gpioa_init(){
    SYSCTL->RCGCGPIO |=(1 << 0);
    while( ! (SYSCTL->PRGPIO & (1 << 0))){}

    GPIOA->AFSEL |= (1 << 0) | (1 << 1);
    GPIOA->PCTL |= (1 << 0) | (1 << 4);
    GPIOA->DEN |= (1 << 0) | (1 << 1);


}


void send_c(char c){
    while(UART0->FR & (1 << 5)){}
    UART0->DR = c;
}


char get_c(){
    while(UART0->FR & (1 << 4)){}
    return UART0->DR ;
}


void sent_string(char * str){
    for(char * c = str; *c; c++){
        send_c(*c);
    }
}




int main(){
    gpioa_init();
    uart_init();
    while (1)
    {

        send_c(get_c());
       
    }
    


    return 0;
}