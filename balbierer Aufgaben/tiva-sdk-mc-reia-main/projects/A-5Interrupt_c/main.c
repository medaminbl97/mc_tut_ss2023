#include <TM4C123GH6PM.h>
#include "gpio.h"
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

void gpiof0_ISR(void)
{
	/*--------------------------------------------Aufgabe Interrupt--------------------------------------------------------------	
		Diese Funktion wird bei Auftritt eines Interrupts aufgerufen
		Der Interrupt ist LEVEL Triggered - wird also ausgelöst wenn sich der Spannungspegel am entsprechenden GPIO ändert
		Im Gegensatz zu Flanken Triggered, wo nur bei Flankenwechsel ein Interrupt auftritt

		Überprüfen Sie zunächst ob der Taster noch gedrückt ist oder schon losgelassen wurde
		Ist der Taster gedrückt aktivieren Sie die entsprechende LED (vgl. Angabe 1. Block)
		
		Ist der Taster NICHT mehr gedrückt deaktivieren Sie die Led

		Denken Sie auch daran, dass am Ende einer Interrupt Service Routine das Interruptflag zurückgesetzt werden muss
		
	----------------------------------------------------------------------------------------------------------------------------*/

}

void gpiof4_ISR(void)
{
	/*--------------------------------------------Aufgabe Interrupt--------------------------------------------------------------	
		Diese Funktion wird bei Auftritt eines Interrupts aufgerufen
		Der Interrupt ist LEVEL Triggered - wird also ausgelöst wenn sich der Spannungspegel am entsprechenden GPIO ändert
		Im Gegensatz zu Flanken Triggered, wo nur bei Flankenwechsel ein Interrupt auftritt

		Überprüfen Sie zunächst ob der Taster noch gedrückt ist oder schon losgelassen wurde
		Ist der Taster gedrückt aktivieren Sie die entsprechende LED (vgl. Angabe 1. Block)
		
		Ist der Taster NICHT mehr gedrückt deaktivieren Sie die Led

		Denken Sie auch daran, dass am Ende einer Interrupt Service Routine das Interruptflag zurückgesetzt werden muss
		
	----------------------------------------------------------------------------------------------------------------------------*/

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

	while (1)
	{
		//hier ist nichts mehr zu tun. Ab jetzt läuft alles über den Interrupt
	}
}
