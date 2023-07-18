#include <stdint.h>
#include <stdbool.h>

/* Driverlib includes */
#include "inc/hw_memmap.h"
#include "gpio.h"
#include "sysctl.h"
#include "systick.h"

#include <TM4C123GH6PM.h>

/*--------------------------------------------Aufgabe Interrupt--------------------------------------------------------------	
	Bisher wurden die zu den beiden Taster gehörigen GPIO Pins ständig abgefragt (Polling)
	In dieser Lektion lernten Sie Interrupts und die Vorteile dieser gegenüber Polling kennen
	Statt der ständigen Abfrage der GPIO Pins der Taster, wird jetzt ein Interrupt ausgelöst 
	Es wird ein LEVEL Triggered Interrupt gewählt. Dieser tritt auf, wenn sich der Spannungspegel ändert.
	Folglich tritt sowohl bei Drücken als auch bei Loslassen des Tasters ein Interrupt auf. 
	
	In Gpio.h finden Sie Beschreibungen der Ihnen zur Verfügung gestellten Funktionen.
	In Gpio.c finden den dazugehörigen Programm Code. 
	
	Ergänzen Sie die mit "Aufgabe Interrupt" gekennzeichneten Bereiche.
			

----------------------------------------------------------------------------------------------------------------------------*/


void gpiof0_ISR(void){

	if(gpiof_readPin(0)){ // Pin status is high, button released
			gpiof_setPin(2, 0); //deactivate LED
		}else{// Pin status is low, button pressed 
		gpiof_setPin(2, 1); 
		}
		gpiof_ICR(0); 
	
}

void gpiof4_ISR(void){

	if(gpiof_readPin(4)){ // Pin status is high 
			gpiof_setPin(1, 0);
			
		}else{
	gpiof_setPin(1, 1);
			
		}
	gpiof_ICR(4); 
}

int main(void)
{
	/* Konfiguration aller benoetigten Pins */
	gpiof_configureInputPin(0); /* PF0: Taster rechts */
	gpiof_configureInputPin(4); /* PF4: Taster links */

	gpiof_configureOutputPin(1); /* PF1: Rote LED */
	gpiof_configureOutputPin(2); /* PF2: Blaue LED */
	gpiof_configureOutputPin(3); /* PF3: Gruene LED */

	/*--------------------------------------------Aufgabe Interrupt--------------------------------------------------------------	
		Aktivieren Sie hier die Edge Interrupts der Taster
		Übergeben Sie auch die entsprechende Funktion, welche in der Interrupt Service Routine aufgerufen wird 
		Die Übergabe der Funktion erfolgt durch Angabe des Funktionsnamen
	
	----------------------------------------------------------------------------------------------------------------------------*/
	activateGpiofEdgeInterrupts(0, gpiof0_ISR);
	activateGpiofEdgeInterrupts(4, gpiof4_ISR);

	while (1)
	{
		//hier ist nichts mehr zu tun. Ab jetzt läuft alles über den Interrupt
	}
}
