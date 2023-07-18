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
    * 1) Ändern sie die folgende Konfiguration so ab, dass ein Interrupt
    *    ausgelöst wird, wenn der Sequencer 0 fertig ist.
    */
    SYSCTL->RCGCADC |= (1 << 0);
    while (!(SYSCTL->PRADC & (1 << 0))) {}

    ADC0->SSPRI = 0;
    ADC0->PC = 0x7;
    ADC0->ACTSS &= ~(1 << 0);
    ADC0->EMUX = 0x0;
    ADC0->SSCTL0 = (1 << 3) | (1 << 7) | (1 << 11) | (1 << 15) | (1 << 14);
    ADC0->SSCTL0 |= (1 << 13);
    ADC0->ACTSS |= (1 << 0);
    ADC0->SAC = 0x02;
    ADC0->IM = (1 << 0); // interrupt sample sequencer 0

    NVIC->ISER[14 / 32] |= (1 << (32%14));
    NVIC->ISER[0] |= (1 << 14);



}

void SysTick_Handler(void)
{
    ADC0->PSSI |= (1 << 0);
}

void init_systick()
{
    SysTick->CTRL = 0;         // Deaktivieren
    SysTick->LOAD = 15999999;  // Setzen des Reload Wertes (Interrupt jede Millisekunde)
    SysTick->VAL = 0;          // Zurücksetzen des Zählers
    SysTick->CTRL |= (1 << 2); // Auswahl der Prozessor Clock (16MHz)
    SysTick->CTRL |= (1 << 1); // Interrupts generieren
    SysTick->CTRL |= (1 << 0); // SysTick aktivieren
}

/** 
 * 2) Implementieren Sie nun den Interrupt Service Handler.
 *    Der Handler soll 
 *    - die Daten vom ADC FIFO lesen, mitteln und in einer 
 *      globalen Variable speichern.
 *    - ein globales Flag setzen, dass neue Daten zur 
 *      Verfügung stehen
 *    - notwendige Verwaltungsarbeit leisten, so dass der Interrupt
 *      erneut ausgelöst werden kann
 */

int value  =0 ;
int flag = 0;


void ADC0Seq0_Handler(){

    ADC0->ISC |= (1 << 0);
    for (size_t i = 0; i < 4; i++)
    {
        vlaue+=ADC0->SSFIFO0;
    }
    value /= 4;
    flag = 1;
    


    
}


int main()
{
    init_uart();
    init_systick();
    init_adc();

    while (1)
    {
        /**
         * 3) Prüfen Sie nun kontinuierlich, ob neue Daten vorhanden sind.
         *    Falls Daten vorhanden sind
         *    - berechnen Sie die Temperatur
         *    - Geben Sie die Temperatur aus
         *    - setzen Sie das Flag zurück
         */
        if(flag != 0){
            float temperature = 147.5 - (75 * 3.3 * value) / 4096.0;
            printf("Temperature: %f\n", temperature);
            flag = 0;
        }
        
    }


}
