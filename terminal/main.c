#include "TM4C123GH6PM.h"

int p = 1000;
int duty_cycle = 5;

int count = 0;
int x = 0;


void gpiof_init(){
    SYSCTL->RCGCGPIO |= (1 << 5);
    GPIOF->AFSEL = 0;
    GPIOF->DIR |= (1 << 1);
    GPIOF->DIR &= ~(1 << 4);
    GPIOF->PUR |= (1 << 4);

    GPIOF->IS &= ~(1 << 4);
    GPIOF->IBE &= ~(1 << 4);
    GPIOF->IEV &= ~(1 << 4);
    GPIOF->IM |= (1 << 4);
    GPIOF->DEN |= (1 << 1) | (1 << 4);
    int int_num = 30;
    NVIC->ISER[0] |= (1 << 30);


}


void GPIOPortF_Handler(){
    if(GPIOF->MIS & (1 << 4)){
        GPIOF->ICR |= (1 << 4);
    duty_cycle += 10;
    if(duty_cycle >= 100) duty_cycle = 0;
    }
}


void systick_init(){
    float  t = 1e-6;
    int load = t * 16e6;
    SysTick->LOAD = load;
    SysTick->CTRL |= 0x7;

}

void SysTick_Handler(){
    x++; 
    if(x == p) x = 0;
    if(x < count){
        GPIOF->DATA |= (1 << 1);
    }else GPIOF->DATA &= ~(1 << 1);

}



void reverse(char * str);
void reverse_all(char ** str,int n);



int main(){
    char  strs [][10] = {"nacuer","ahmed","jawher","rania","achref"};
    char ** nc = strs;
    
    reverse(strs[0]);
    reverse_all(strs,5);
   
    
    while (1)
    {
        /* code */
    }
    


    return 0;
}