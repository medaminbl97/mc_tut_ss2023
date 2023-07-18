#include "TM4C123GH6PM.h"


void portf_init(){
    SYSCTL->RCGCGPIO |= (1 << 5) ;
    while(   !(SYSCTL->PRGPIO & (1 << 5))   ){}

    GPIOF->AFSEL &= ~((1 << 3) | (1 << 4));
    GPIOF->DIR &= ~(1 << 4);
    GPIOF->DIR |= (1 << 3);
    GPIOF->DEN |= (1 << 3) | (1 << 4);
    GPIOF->PUR |= (1 << 4);

    GPIOF->IS &= ~(1 << 4); 
    GPIOF->IBE &= ~(1 << 4);
    GPIOF->IEV &= ~(1 << 4);
    GPIOF->IM |= (1 << 4);

    int gpiof_interrupt_nummer = 30;
    int iser_block = gpiof_interrupt_nummer / 32;
    int iser_bit_stelle = gpiof_interrupt_nummer % 32;


    NVIC->ISER[iser_block] = (1 << iser_bit_stelle );


}


void GPIOPortF_Handler(){
    if(GPIOF->MIS & (1 << 4)){
        GPIOF->ICR |= (1 << 4);

        GPIOF->DATA ^= (1 << 3);
        ADC0->PSSI |= (1 << 3);
        
    }
    
   
}


void adc_init(){
    SYSCTL->RCGCADC |= (1 << 0);
    while(!(SYSCTL->PRADC &(1 << 0))){}

    SYSCTL->RCGCGPIO |= (1 << 3) ;
    while(   !(SYSCTL->PRGPIO & (1 << 3))   ){}

    GPIOD->AFSEL |= (1 << 3);
    GPIOD->AMSEL |= (1 << 3);
    GPIOD->DEN &= ~(1 << 3);



    ADC0->ACTSS &= ~0xf;
    ADC0->SSMUX3 |= (1 << 2);
    ADC0->SSCTL3 |= (1 << 1);
    ADC0->EMUX &= ~(0xf << 12);
    ADC0->ACTSS |= (1 << 3);
    
    ADC0->SS








}





int main(){
    portf_init();
    adc_init();
    while (1)
    {
        
    }
    
    return 0;
}