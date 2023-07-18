#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define DELAYVAL	16000000    //equals 1s

/*  Diese Methode konfiguriert den Timer 0A mit Interrupts.
 *  
 *      reloadVal - Wert der zum Laden des RELOAD Registers verwendet wird
 *      void (*pFunc)(void) - Funktionspointer auf die bei Interrupt Auslösung
 *														auszuführende Funktion
 *              
 *  Bei ungueltigen Pinnummern passiert nichts.
 * 
 */
void timer0_configureWithInterrupt(uint32_t reloadVal, void (*pFunc)(void));

/*  Diese Methode setzt das Interruptflag zurück. Am Ende eines Handler Aufrufs/ am Ende einer
 *  einer Interrupt Service Routine muss das Interruptflag zurück gesetzt werden.
 * 
 */
void timer0_ICR(void);

#endif
