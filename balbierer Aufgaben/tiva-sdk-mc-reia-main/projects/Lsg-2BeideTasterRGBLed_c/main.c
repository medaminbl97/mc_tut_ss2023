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
	SYSCTL->RCGCGPIO	|= 0x20;
	/* Enable clock for GPIO F */
	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->CR = 0xff;
	 
	/* Set direction for pin 0 and 1
	 *	PF0		input			bit low
	 *	PF1		output		bit high
	 */
	GPIOF->DIR= 0x0e;
	 /* Disable Alternate function for both pins */
	GPIOF->AFSEL	&= ~0xff;
	 
	 /* Enable pullup for PF0 */
	 GPIOF->PUR		|= 0x11;
	 
	 /* Enable digital function for both pins */
	 GPIOF->DEN		|= 0x1f;



	//GPIOF->DATA = 0x02;

	//Enable Pins PF0 and PF1
	 
	/* Set direction for pin 0 and 1
	 *	PF0		input			bit low
	 *	PF1		output		bit high
	 */
	 
	 /* Disable Alternate function for both pins */
	 
	 /* Enable pullup for PF0 */
	 
	 /* Enable digital function for both pins */
GPIOF->DATA	|= 0x08;
	while(1)
	{
	 	if (GPIOF->DATA & 0x01) {
		
			GPIOF->DATA	&= ~0x02;
		 }else{
		
		GPIOF->DATA	|= 0x02;
		 }

		if (GPIOF->DATA & 0x10) {
			
			GPIOF->DATA	&= ~0x04;
		}else{

			GPIOF->DATA	|= 0x04;
		}

		
//		if (!GPIOF->DATA & 0x08) {
			/* Button value high -> button not pressed -> LED off */
//			GPIOF->DATA	|= 0x04;
//		 }

	//	if((GPIOF->DATA&0x01)){

	//		GPIOF->DATA |= 0x04;
	//	}

		/*if(!(GPIOF->DATA&0x01)){

			GPIOF->DATA &=~  0x04;
		}
		

		if(GPIOF->DATA&0x10){

			GPIOF->DATA |= 0x08;
		}
		if(!(GPIOF->DATA&0x10)){

			GPIOF->DATA &=~ 0x08;
		}
		
		/* Read button value:
		 *	Due to the pull-up on PF0 and the button connected between the pin and ground
		 *	the pin value is HIGH (1) when the button is not pressed and LOW (0) when it is
		 *	pressed.
		 */

	}
}