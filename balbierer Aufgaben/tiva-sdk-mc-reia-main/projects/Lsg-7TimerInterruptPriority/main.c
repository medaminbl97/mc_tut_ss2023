#include <stdint.h>
#include <stdbool.h>

/* Driverlib includes */
#include "inc/hw_memmap.h"

//#include <TM4C123GH6PM.h>
#include "timer.h"
#include "gpiof.h"

/*--------------------------------------------Aufgabe Timer Interrupt Priority--------------------------------------------------------------	
	Diese Übung soll zeigen, wie sich Interrupts gegenseitig unterbrechen können (Stichwort Interruptpriorität).
	Dazu sollen die Interrupts für einen Taster Level-Triggerd und für einen Taster Edge-Triggered eingestellt werden.
	Zuden werden wir heute die Timer Baugruppe zum erstem mal initialisieren und damit eine LED zyklisch zum blinken bringen. 
	Folgendes soll das Programmam ende können:
	 -	Der Timer wurde initialisiert und löst jede Sekunde einen Interrupt aus. 
	 	In diesem soll die grüne LED getoggelt werden.
		Verwenden sie für dieses Projekt den Timer 0A und konfigurieren sie ihn als 32-bit Timer der periodisch weiterläuft 
		sobald er gestartet wurde. 
	 -	Die beiden Taster und alle drei LEDs wurden entsprechend initialisiert.
	 	Wird der linke Taster gedrückt soll die rote LED über einen Level-Triggered Interrupt angeschalten und
		ausgeschalten werden. Die Entscheidung ob die LED an oder ausgeschalten wird, wird über den Zustand des 
		Tasters entschieden. Ist der Taster gedrückt geht die LED an, ist der Taster nicht gedrückt geht die LED aus.
		Wird der rechte Taser gedrückt soll die blaue LED über einen Edge-Triggered Interrupt (Both Edges) angeschalten 
		und ausgeschalten werden. Die Entscheidung ob die LED an oder ausgeschalten wird, wird über den Zustand des 
		Tasters entschieden. Ist der Taster gedrückt geht die LED an, ist der Taster nicht gedrückt geht die LED aus.

	In Gpiof.h finden Sie Beschreibungen der Ihnen zur Verfügung gestellten Funktionen für die GPIOs.
	In Gpiof.c finden den dazugehörigen Programm Code für die GPIOs. 
	In timer.h finden Sie Beschreibungen der Ihnen zur Verfügung gestellten Funktionen für die Timer Baugruppe.
	In timer.c finden den dazugehörigen Programm Code für die Timer Baugruppe. 
----------------------------------------------------------------------------------------------------------------------------*/


void gpiof0_ISR(void)
{
	if (gpiof_readPin(0))		// Pin status is high, button released
	{						
		gpiof_setPin(2, 0); 	// turn off blue LED
	}
	else						// Pin status is low, button pressed
	{ 
		gpiof_setPin(2, 1);		// turn on blue LED
	}
}

void gpiof4_ISR(void)
{
	if (gpiof_readPin(4))		// Pin status is high, button released
	{
		gpiof_setPin(1, 0);		// turn off red LED
	}
	else						// Pin status is low, button pressed
	{
		gpiof_setPin(1, 1);		// turn on red LED
	}
} 

void timer0_ISR(void)
{
	gpiof_togglePin(3);		//toggle green LED
}

int main(void)
{
	//GPIOs initialisieren
	gpiof_configureInputPin(0); /* PF0: Taster rechts */
	gpiof_configureInputPin(4); /* PF4: Taster links */

	gpiof_configureOutputPin(1); /* PF1: Rote LED */
	gpiof_configureOutputPin(2); /* PF2: Blaue LED */
	gpiof_configureOutputPin(3); /* PF3: Gruene LED */
	
	activateGpiofEdgeInterrupts(0, gpiof0_ISR);		/* Aktiviere Level IRQ für linken Taster */
	activateGpiofLevelInterrupts(4, gpiof4_ISR);	/* Aktiviere Edge IRQ für rechten Taster */

	/* Timer initialisieren und starten */
	timer0_configureWithInterrupt(DELAYVAL, timer0_ISR);

	while (1)
	{
		//hier ist nichts mehr zu tun. Ab jetzt läuft alles über den Interrupt
		
		// workaround: low level irq kann led nicht ausschalten
		gpiof_setPin(1, 0);		// turn off red LED
	}
}
