#include "TM4C123GH6PM.h"
#include <stdio.h>


void adc_init(){
    SYSCTL->RCGCADC |= (1 << 0);
    while(! (SYSCTL->PRADC & (1 << 0))) {}

    ADC0->ACTSS &= ~(1 << 0); // disable ss0

    ADC0->SSMUX0 |= (4 << 0); // ain4 für ss0 auswähleb

    ADC0->SSCTL0 = 0;
    ADC0->SSCTL0 |= (1 << 1);  // sampling endet bei ain4

    ADC0->EMUX &= ~0xF; // Processer zum  initialisirung von ss0, dabei nutuzt man dann PSSI wie untne 

    ADC0->ACTSS |= (1 << 0);// enable ss0

    ADC0->PSSI |= (1 << 0);  // initialize ss0

}


void ain4_init(){

    SYSCTL->RCGCGPIO |= (1 << 3);
    GPIOD->AFSEL |= (1 << 3);
    GPIOD->AMSEL |= (1 << 3);
    GPIOD->DEN &= ~(1 << 3);

}

void uart_init(){
    SYSCTL->RCGCUART |= (1 << 0);
    while(! (SYSCTL->PRUART & (1 << 0))) {}

    SYSCTL->RCGCGPIO |= (1 << 0);
    GPIOA->AFSEL |= (1 << 0) | (1 << 1);
    GPIOA->PCTL |= (1 << 0) | (1 << 4);
    GPIOA->DEN |= (1 << 0) | (1 << 1);





    int baudrate = 9600;
    int ibrd = 16e6 / (16 * 9600);
    int fbrd = ( 16e6 / (16 * 9600) - ibrd) * 64 + 0.5;

    UART0->IBRD = ibrd;
    UART0->FBRD = fbrd;
    UART0->LCRH |= (3 << 5) |(1 << 4);
    UART0->CTL |= (1 << 0);







}


void send_c(char c){
    while (UART0->FR & (1 << 5))
    {
    }

    UART0->DR = c;

    
}

void send_string_1(char * str){
    for (char * i = str; *i ; i++)
    {
        send_c(*i);
    }
    
}




int main(){
    ain4_init();
    uart_init();
    adc_init();

    while (1)
    {
        short value = 0;
        while(ADC0->ACTSS & (1 << 16)){}
        ADC0->PSSI |= (1 << 0);
        value = ADC0->SSFIFO0 ;
        float voltage = value / 4095 * 3300;

        char buffer[128] ;
        sprintf(buffer,"Voaltage = %f\n",voltage);

        send_string_1(buffer);



    }
    


    return 0;
}