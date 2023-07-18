#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
/* Driverlib includes */
#include "inc/hw_memmap.h"


#include "printf.h"
#include "uart.h"


#include <string.h>


void init_adc()
{
   /**
    * 1) Initialisieren Sie hier den ADC mit der im Datenblatt 
    *    beschriebenen Reihenfolge. Folgende Konfiguration ist
    *    gewünscht:
    * 
    * SampleSequencer0:
    * - 4 x Abtasten des Temperatursensors
    * - Nach 4x Temperatursensor soll der Sequencer aufhören
    * - Es soll kein Interrupt ausgelöst werden
    * 
    * ADC Averaging: 
    * - Die Messwerte sollen 4x überabgetastet werden
    * 
    * ADC:
    * - 1 MSample / s
    * - Triggerung von SampleSequencer 0 durch den Prozessor
    */

    SYTCTL->RCGCADC |= (1 << 0);
    while (!(SYTCTL->PRADC & (1 << 0)))
    {
    }

    ADC0->ACTSS = 0;

    ADC0->SSMUX0 = 0;
    ADC0->SSCTL0 = 0;
    ADC0->SSCTL0 |= (1 << 3) | (1 << 7) | (1 << 11) |(1 << 15) | (1 << 13);
    ADC0->EMUX &= ~(1 << 0);

    ADC0->ACTSS =| (1 << 0);


    


}

void SysTick_Handler(void)
{
    /**
     * 2) Triggern Sie hier den Sample Sequencer 0,
     *    um eine Messung zu starten
     */

    ADC0->PSSI |= (1 << 0);
}

void init_systick()
{
    SysTick->CTRL = 0;         // Deaktivieren
    SysTick->LOAD = 15999999;  // Setzen des Reload Wertes (Interrupt jede Sekunde)
    SysTick->VAL = 0;          // Zurücksetzen des Zählers
    SysTick->CTRL |= (1 << 2); // Auswahl der Prozessor Clock (16MHz)
    SysTick->CTRL |= (1 << 1); // Interrupts generieren
    SysTick->CTRL |= (1 << 0); // SysTick aktivieren
}

int main()
{
    uint32_t counter = 0;
    uint8_t rcvbuffer;

    init_uart();
    init_systick();
    init_adc();

    while (1)
    {
        /**
         * 3) Warten Sie hier in der Schleife darauf, dass 
         *    Daten im ADC Fifo von Sequencer 0 gelandet sind
         *    und der ADC nicht mehr BUSY ist
         */

         while(ADC0->ACTSS & (1 << 16)){ // warten }

        /** 
         * 4) Lesen Sie nun die Daten vom FIFO und berechnen
         *    Sie den Mittelwert
         */

        /*uint16_t x1 = ADC=->SSFIFO0;
        uint16_t x2 = ADC=->SSFIFO0;
        uint16_t x3 = ADC=->SSFIFO0;
        uint16_t x4 = ADC=->SSFIFO0;
        uint16_t m = (x1 +x2 + x3 + x4)/4;*/

        uint16_t value = 0;

        for (size_t i = 0; i < 4; i++)
        {
            value += ADC=->SSFIFO0;
        }


        // 2^12 --> 4095 -- 3.3v
        //      --> fifo_value -- spanung --> spannung = (fifo_value / 4095) * 3300
        value /= 4;
        float spannung = (value / 4095.0) * 3300;
        

        /**
         * 5) Berechnen Sie anhand der im Datenblatt gegebenen Formel
         *    und des in 4) berechneten Mittelwerts die aktuelle Temperatur 
         */

        float temp = (2700 - spannung)*75 - 55; 

        /** 
         * 6) Geben Sie die Temperatur mittels printf aus
         */
        char buffer [128];
        sprintf(buffer,"hallo, %f",temp);
        

        printf("hallo, %f",temp);
    }
}
