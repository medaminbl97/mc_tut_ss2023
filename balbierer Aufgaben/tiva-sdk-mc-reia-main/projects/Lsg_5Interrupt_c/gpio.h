#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/*  Diese Methode konfiguriert den uebergebenen Pin der GPIO Baugruppe F 
 *  als Eingang (Input).
 * 
 *      pinNr - Nummer des Pins (0 bis 7)
 *              
 *  Bei ungueltigen Pinnummern passiert nichts.
 * 
 */
void gpiof_configureInputPin(uint8_t pinNr);

/*  Diese Methode konfiguriert den uebergebenen Pin der GPIO Baugruppe F 
 *  als Ausgang (Output).
 * 
 *      pinNr - Nummer des Pins (0 bis 7)
 *              
 *  Bei ungueltigen Pinnummern passiert nichts. 
 * 
 */
void gpiof_configureOutputPin(uint8_t pinNr);

/*  Diese Methode setzt einen als Ausgang konfigurierten Pin auf den 
 *  uebergebenen Logikpegel.
 * 
 *      pinNr - Nummer des Pins (0 bis 7)
 *      value - neuer Logikpegel: '0' -> Low-Pegel (0V)
                                  '1' -> High-Pegel (3,3V)
 *              
 *  Bei ungueltigen Pinnummern oder falsch konfigurierten Pins passiert nichts. 
 * 
 */
void gpiof_setPin(uint8_t pinNr, uint8_t value);

/*  Diese Methode gibt den aktuellen Logikpegel eines als Eingang konfigurierten
 *  Pins zurueck.
 * 
 *      pinNr - Nummer des Pins (0 bis 7)
 *      
 *      Rueckgabe - aktueller Logikpegel: Low-Pegel (0V) -> '0'
 *                                        High-Pegel (3,3V) -> '1'
 *              
 *  Bei ungueltigen Pinnummern oder falsch konfigurierten Pins wird '0' 
 *  zurueckgegeben.
 * 
 */
uint8_t gpiof_readPin(uint8_t pinNr);

/*  Diese Methode aktiviert den Edge Interrupt des übergebenen GPIOF Pins. 
 * 	Wird ein Interrupt ausgelöst wird die als Funktionspointer übergebenen 
 *	Methode ausgeführt.
 * 
 *      pinNr - Nummer des Pins (0 bis 7)
 *      
 *      void (*pFunc)(void) - Funktionspointer auf die bei Interrupt Auslösung
 *														auszuführende Funktion             
 * 
 */
void activateGpiofEdgeInterrupts(uint8_t pinNr, void (*pFunc)(void));

/*  Diese Methode überprüft ob an dem jeweiligen Pin das Interrupt Flag gesetzt und 
 * 	somit ein Interrupt ausgelöst wurde. 
 * 
 *      pinNr - Nummer des Pins (0 bis 7)
 *      
 *      Rueckgabe - bei gesetztem Interruptflag -> '1'
 *                  ansonsten -> '0'
 *              
 */
uint8_t gpiof_RIS(uint8_t pinNr);

/*  Diese Methode setzt das Interruptflag zurück. Am Ende eines Handler Aufrufs/ am Ende einer
 *  einer Interrupt Service Routine muss das Interruptflag zurück gesetzt werden.
 * 
 *      pinNr - Nummer des Pins (0 bis 7)          
 * 
 */
void gpiof_ICR(uint8_t pinNr);

#endif
