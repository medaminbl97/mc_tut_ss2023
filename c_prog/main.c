#include "TM4C123GH6PM.h"


int str_length(char * str);
void upper_case(char * str,int len);

typedef unsigned int uint_32;



typedef struct {
    uint_32 offset[255];
    uint_32 data;
    uint_32 dir;
    uint_32 offset1[7];
    uint_32 afsel;
    uint_32 offset2[62];
    uint_32 den;
}gpio;

uint_32 *rcgc = (uint_32*) 0x400FE608;
gpio * portf = (uint_32*) 0x40025000;
gpio * porta = (uint_32*) 0x40004000;


int main(){
    /*char name[]=  "naceur";
    char * ptr = name;

    int l = str_length(name);*/

    SYSCTL->RCGCGPIO  |= (1 << 5);
    GPIOF->AFSEL &= ~(1 << 1);
    GPIOF->DIR |=  (1 << 1);
    GPIOF->DEN |=  (1 << 1);
    while (1)
    {
        GPIOF->DATA ^=  (1 << 1);
        for (int i = 0; i < 0xfffff; i++)
        {
        }
        
    }
    
    


    return 0; 
}