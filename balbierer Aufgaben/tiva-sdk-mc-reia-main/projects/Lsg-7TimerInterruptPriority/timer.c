#include <stddef.h>
#include "TM4C123GH6PM.h"
#include "definitions.h"
#include "timer.h"

/* 
*	Definition des Funktionsarrays für die Callback-Funktionen bei 
*	Auslösen eines GPIO Interrupts  
*/
pFunc fctArrayTimer = NULL;


/*-------------------------------------------timer0_configureWithInterrupt(uint32_t reloadVal, void (*pFunc)(void))----------------------------------------------------*/
void timer0_configureWithInterrupt(uint32_t reloadVal, void (*pFunc)(void))
{
	/* Timer Baugruppe aktivieren, falls noch nicht geschehen */
    if ((SYSCTL->RCGCTIMER & (0x01 << 0)) == 0x00)
    {
        SYSCTL->RCGCTIMER |= (0x01 << 0);
    }

	/* Timer0A ausschalten */
	TIMER0->CTL	&= ~0x01;

	/* 32-bit timer auswählen */
	TIMER0->CFG	= 0x00;

	/* Periodic mode aktivieren */
	TIMER0->TAMR |= 0x02;

	/* Reload value laden */
	TIMER0->TAILR = reloadVal;

	/*
	* Interrupt konfigurieren: Time-Out Interrupt -> kommt beim Überlauf des Timers 
	* Interrupt Priorität: niedrigste Priorität 
	*/
	TIMER0->IMR |= 0x01;
	NVIC->ISER[0] |= 0x01<<19;
	NVIC->IP[19] = (0x07<<5);	

	/* Callback Funktion setzen*/
	fctArrayTimer = (*pFunc);
	
	/* Timer wieder anschalten */
	TIMER0->CTL |= 0x01;
}

/*-----------------------------------------------------------timer0_ICR(void)----------------------------------------------------------*/
void timer0_ICR(void)
{
	/* Time-Out Interrupt zurücksetzen */
    TIMER0->ICR |= 0x01;
}

/*-----------------------------------------------------------Timer0A_Handler(void)----------------------------------------------------------*/
void Timer0A_Handler(void)
{
	if (fctArrayTimer != NULL)
    {
		fctArrayTimer();
	}
	
	timer0_ICR();
}

