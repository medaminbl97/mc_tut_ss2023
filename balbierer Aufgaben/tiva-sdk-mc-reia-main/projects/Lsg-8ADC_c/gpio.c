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
    if (pinNr > 7)
    {
        return;
    }

    /* GPIOF Baugruppe aktivieren, falls noch nicht geschehen */
    if ((SYSCTL->RCGCGPIO & 0x01 << 5) == 0x00)
    {
        SYSCTL->RCGCGPIO |= 0x01 << 5;
    }

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
        GPIOF->DIR &= ~(0x01 << pinNr);

        /* Pull-up Widerstand aktivieren 
         * In diesem Beispiel wird das fuer alle Input Pins gemacht, da saemtliche
         * Inputs fuer Taster verwendet werden */
        GPIOF->PUR |= (0x01 << pinNr);
    }
    else
    {
        /* Pin als Output konfigurieren */
        GPIOF->DIR |= (0x01 << pinNr);
    }

    /* Alternative Funktionen deaktivieren */
    GPIOF->AFSEL &= ~(0x01 << pinNr);

    /* Digitale Funktionen aktivieren */
    GPIOF->DEN |= (0x01 << pinNr);
}

/*----------------------------------------------gpiof_configureInputPin(uint8_t pinNr)----------------------------------------------------*/
void gpiof_configureInputPin(uint8_t pinNr)
{
    /* Interne Hilfsfunktion mit Typen '0' fuer Input aufrufen */
    configurePin(pinNr, 0);
}

/*----------------------------------------------gpiof_configureOutputPin(uint8_t pinNr)----------------------------------------------------*/
void gpiof_configureOutputPin(uint8_t pinNr)
{
    /* Interne Hilfsfunktion mit Typen '1' fuer Output aufrufen */
    configurePin(pinNr, 1);
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
        GPIOF->DATA &= ~(0x01 << pinNr);
    }
    else
    {
        GPIOF->DATA |= (0x01 << pinNr);
    }
}

/*-----------------------------------------------------gpiof_readPin(uint8_t pinNr))---------------------------------------------------------*/
uint8_t gpiof_readPin(uint8_t pinNr)
{
    /* Uebergebene Pinnummer und entsprechende Konfiguration pruefen. Bei 
     * Fehlern wird die Funktion mit Rueckgabeparameter '0' verlassen */
    if ((pinNr > 7) || ((GPIOF->DIR & 0x01 << pinNr) > 0))
    {
        return 0;
    }

    /* Aktuellen Logikpegel auslesen */
    if ((GPIOF->DATA & 0x01 << pinNr) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
    // oder: return !((GPIOF->DATA & 0x01 << pinNr) == 0);
}

/*----------------------------------activateGpiofEdgeInterrupts(uint8_t pinNr, void (*pFunc)(void))-------------------------------------------*/
void activateGpiofEdgeInterrupts(uint8_t pinNr, void (*pFunc)(void))
{
    if (pinNr > 7)
    {
        return;
    }

    fctArray[pinNr] = (*pFunc);

    GPIOF->IS &= ~(0x01 << pinNr); // Edge Interrupts einstellen
    GPIOF->IBE |= (0x01 << pinNr); // Beide Flanken (steigende und fallende)
    GPIOF->IM |= (0x01 << pinNr);  // Interrupt freigeben
    NVIC->ISER[0] |= 0x01 << 30;   // Im NVIC aktivieren
    NVIC->IP[30] = (0x00 << 5);
}

/*-----------------------------------------------------------gpiof_RIS(uint8_t pinNr)----------------------------------------------------------*/
uint8_t gpiof_RIS(uint8_t pinNr)
{
    if (GPIOF->RIS & 0x01 << pinNr)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    // oder: return (GPIOF->RIS & 0x01 << pinNr);
}

/*-----------------------------------------------------------gpiof_ICR(uint8_t pinNr)----------------------------------------------------------*/
void gpiof_ICR(uint8_t pinNr)
{
    if (pinNr > 7)
    {
        return;
    }

    GPIOF->ICR |= 0x01 << pinNr;
}

/*-----------------------------------------------------------GPIOF_Handler(void)----------------------------------------------------------*/
/*
void GPIOF_Handler(void)
{
	if (GPIOF->RIS & 0x01<<4) 
	{
		// Switch 1 caused interrupts
				
		if (GPIOF->DATA	& 0x01<<4)
		{
			// Pin status is high now, button released
			GPIOF->DATA	&= ~(0x01<<1);
		}
		else 
		{
			// Pin status is low now, button pressed
			GPIOF->DATA |= 0x01<<1;
		}
		
		GPIOF->ICR	|= 0x01<<4;
	}
	else if (GPIOF->RIS & 0x01<<0)
	{
		// Switch 2 caused interrupt
			
		if (GPIOF->DATA	& 0x01<<0)
		{
			// Pin status is high now, button released
			GPIOF->DATA	&= ~(0x01<<2);
		}
		else 
		{
			// Pin status is low now, button pressed
			GPIOF->DATA |= 0x01<<2;
		}
		
		GPIOF->ICR	|= 0x01<<0;
	}
}*/

void GPIOPortF_Handler(void)
{
    if (gpiof_RIS(4)) // Check if Switch 1 caused interrupts
    {
        if (fctArray[4] != NULL)
            fctArray[4]();
    }

    if (gpiof_RIS(0)) // Check if Switch 2 caused interrupts
    {
        if (fctArray[0] != NULL)
            fctArray[0]();
    }
}
