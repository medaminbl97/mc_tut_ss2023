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
	/* -----------------------------Pin configuration:-----------------------------------
	 *	PF0		SW 2
	 *  PF4		SW 1
	 * 
	 *	PF1		red LED
	 *	PF2		blue LED
	 *	PF3		green LED	
	 ------------------------------------------------------------------------------------*/



	/* ------------------------------------------Init-----------------------------------*/
	
	
	/* Enable clock for GPIO F */

	/* Unlock GPIO F - Unlock Sequence: 0x4C4F434B */

	/* Enable Write to GPIOAFSEL, GPIOPUR, GPIODR, GPIODEN*/
	 
	/* Set direction for pin 0-4
	 */
	
	 /* Disable Alternate function for both pins */

	 
	 /* Enable pullup for PF0 & PF4*/
	 
	 /* Enable digital function for pins 0-4*/


	while(1)
	{
		/* Read button value:
		 *	Due to the pull-up on PF0 and the button connected between the pin and ground
		 *	the pin value is HIGH (1) when the button is not pressed and LOW (0) when it is
		 *	pressed.
		 */

	}
}
