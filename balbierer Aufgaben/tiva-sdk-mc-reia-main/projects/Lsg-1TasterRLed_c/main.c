#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
/* Driverlib includes */
#include "inc/hw_memmap.h"
#include "gpio.h"
#include "sysctl.h"
#include "systick.h"

int main(void)
{
	/* Pin configuration:
	 *	PF0		SW 2
	 *	PF1		red LED
	 */
	
	
	/* Enable clock for GPIO F */
	SYSCTL->RCGCGPIO	|= 0x01<<5;
	
	//Enable Pins PF0 and PF1

	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->CR = 0xFF;
	 
	/* Set direction for pin 0 and 1
	 *	PF0		input			bit low
	 *	PF1		output		bit high
	 */
	 GPIOF->DIR		&= ~(0x01<<0);
	 GPIOF->DIR		|= 0x01<<1;
	 /*GPIOF->DIR |= (0x01<<PinNR);*/
	 
	 /* Disable Alternate function for both pins */
	 GPIOF->AFSEL	&= ~(0x01<<0 | 0x01<<1);
	 
	 /* Enable pullup for PF0 */
	 GPIOF->PUR		|= 0x01<<0;
	 
	 /* Enable digital function for both pins */
	 GPIOF->DEN		|= (0x01<<0 | 0x01<<1);

	while(1)
	{
		/* Read button value:
		 *	Due to the pull-up on PF0 and the button connected between the pin and ground
		 *	the pin value is HIGH (1) when the button is not pressed and LOW (0) when it is
		 *	pressed.
		 */
		 if (GPIOF->DATA & 0x01<<0) {
			/* Button value high -> button not pressed -> LED off */
			GPIOF->DATA	&= ~(0x01<<1);
		 }
		 else {
			/* Button value low -> button pressed -> LED on */
			GPIOF->DATA	|= 0x01<<1;
		 }
	}
}
