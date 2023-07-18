#include "gpio.h"
#include <stddef.h>
#include "TM4C123GH6PM.h"

typedef void (*pFunc)(void);
pFunc fctArray[7];

/*-------------------------------------------configurePin(uint8_t pinNr, uint8_t type)----------------------------------------------------*/
void configurePin(uint8_t pinNr, uint8_t type)
{
    /* Uebergebene Pinnummer pruefen. Falls außerhalb des gueltigen
     * Bereichs, Funktion verlassen */

    /* GPIOF Baugruppe aktivieren, falls noch nicht geschehen */

    /* PF0 entsperren, falls relevanter Pin */
    if (pinNr == 0)
    {
        GPIOF->LOCK = 0x4C4F434B;
        GPIOF->CR |= 0x01 << 0;
    }

    /* Pin entsprechend konfigurieren */
    if (type == 0)
    {
        /* Pin als Input konfigurieren */

        /* Pull-up Widerstand aktivieren 
         * In diesem Beispiel wird das fuer alle Input Pins gemacht, da saemtliche
         * Inputs fuer Taster verwendet werden */
    }
    else
    {
        /* Pin als Output konfigurieren */
    }

    /* Alternative Funktionen deaktivieren */

    /* Digitale Funktionen aktivieren */
}

/*----------------------------------------------gpiof_configureInputPin(uint8_t pinNr)----------------------------------------------------*/
void gpiof_configureInputPin(uint8_t pinNr)
{
    /* Interne Hilfsfunktion mit Typen '0' fuer Input aufrufen */
}

/*----------------------------------------------gpiof_configureOutputPin(uint8_t pinNr)----------------------------------------------------*/
void gpiof_configureOutputPin(uint8_t pinNr)
{
    /* Interne Hilfsfunktion mit Typen '1' fuer Output aufrufen */
}

/*----------------------------------------------gpiof_setPin(uint8_t pinNr, uint8_t value)----------------------------------------------------*/
void gpiof_setPin(uint8_t pinNr, uint8_t value)
{
    /* Uebergebene Pinnummer pruefen. Falls außerhalb des gueltigen
     * Bereichs, Funktion verlassen */
    if (pinNr > 7)
    {
        return;
    }

    /* Neuen Logikpegel setzen */
    if (value == 0)
    {
        /* GPIO DATA bit clear an entspr. pin */
    }
    else
    {
        /* GPIO DATA bit setan entspr. pin */
    }
}

/*-----------------------------------------------------gpiof_readPin(uint8_t pinNr))---------------------------------------------------------*/
uint8_t gpiof_readPin(uint8_t pinNr)
{
    /* Uebergebene Pinnummer und entsprechende Konfiguration pruefen. Bei 
     * Fehlern wird die Funktion mit Rueckgabeparameter '0' verlassen */

    /* Aktuellen Logikpegel auslesen */
}

/*----------------------------------activateGpiofEdgeInterrupts(uint8_t pinNr, void (*pFunc)(void))-------------------------------------------*/
void activateGpiofEdgeInterrupts(uint8_t pinNr, void (*pFunc)(void))
{
    if (pinNr > 7)
    {
        return;
    }

    fctArray[pinNr] = (*pFunc);

    // Edge Interrupts einstellen
    // Beide Flanken (steigende und fallende)
    // Interrupt freigeben
    // Im NVIC aktivieren
}

/*-----------------------------------------------------------gpiof_RIS(uint8_t pinNr)----------------------------------------------------------*/
uint8_t gpiof_RIS(uint8_t pinNr)
{
    /*ist am entsprechenden Pin ein Interrupt aufgetreten?*/
    // ja - return 1
    // nein - return 0
}

/*-----------------------------------------------------------gpiof_ICR(uint8_t pinNr)----------------------------------------------------------*/
void gpiof_ICR(uint8_t pinNr)
{
    if (pinNr > 7)
    {
        return;
    }

    //Interrupt Clear am entsprechenden PIN
}

/*-----------------------------------------------------------GPIOF_Handler(void)----------------------------------------------------------*/

void GPIOPortF_Handler(void)
{
    // Check if Switch 1 caused interrupts

    // if so: entsprechende Funktion über Funktionspointerarray aufrufen

    // Check if Switch 2 caused interrupts

    // if so: entsprechende Funktion über Funktionspointerarray aufrufen
}
