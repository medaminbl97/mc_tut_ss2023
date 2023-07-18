#include "TM4C123GH6PM.H"


int main(void)
{
//LED initialisieren
	SYSCTL->RCGCGPIO 	|= 0x01<<5;
	GPIOF->DIR 			|= (0x01<<1);	
	GPIOF->AFSEL 		&= ~(0x01<<1);
	GPIOF->PUR 			&= ~(0x01<<1);	
	GPIOF->DEN			|= (0x01<<1);
	
	SysTick->CTRL		&= ~(0x01<<0); //SysTick ausschalten
	SysTick->LOAD		= 4e6;				 //SysTick load Value setzen (entspricht einer Sekunde)
	SysTick->CTRL		&= ~(0x01<<2);
	SysTick->CTRL		|= 0x03<<0;		 //SysTick einschalten und Interrupt Aktivieren; Clock Source ist der precission internal oszillator (poisc/4 = 4 MHz)
		
	while(1)
	{
	}
}

void SysTick_Handler(void)
{
	
		GPIOF->DATA ^= 0x01<<1;					//rote LED toggeln

}
