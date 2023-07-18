#include <stdint.h>
#include <stdbool.h>

/* Driverlib includes */
#include "inc/hw_memmap.h"
#include "gpio.h"
#include "sysctl.h"
#include "systick.h"

#include "TM4C123GH6PM.H"
#include "printf.h"
#include "adc.h"
#include "gpio.h"
#include <stdint.h>
#include <string.h>

#define UART0_RX_PIN        0
#define UART0_TX_PIN        1
#define UARTx_TXFF          5
#define UARTx_RXFE          4

void gpiof0_ISR(void){

	if(gpiof_readPin(0)){ // Pin status is high, button released
			gpiof_setPin(2, 0); //deactivate LED
		}else{// Pin status is low, button pressed 
		gpiof_setPin(2, 1); 
           printf("Button F0 Pressed\n");
		}
		gpiof_ICR(0); 
	
	gpiof_ICR(0);
}



void gpiof4_ISR(void){

	if(gpiof_readPin(4)){ // Pin status is high 
			gpiof_setPin(1, 0);
			
		}else{
	gpiof_setPin(1, 1);
			printf("Button F4 Pressed\n");
		}
	gpiof_ICR(4); 
}

void init_gpio()
{
    /**
     *  1) Initialisieren Sie in dieser Funktion die Pins des UART so, dass 
     *     sie für den UART verwendet werden können
     */
    
    // Siehe Datenblatt Seite 657

    // 1.1) Clock aktivieren
    SYSCTL->RCGCGPIO |= (1 << 0);           // Clock von GPIOA anschalten
    while (!(SYSCTL->PRGPIO & (1 << 0))) {} // Warten, bis das Modul bereit ist

    // 1.2) Richtung (Eingang/Ausgang) konfigurieren
    GPIOA->DIR &= ~(1 << UART0_RX_PIN);     // A0 als Eingang konfigurieren (Rx)
    GPIOA->DIR |= (1 << UART0_TX_PIN);      // A1 als Ausgang konfigurieren (Tx)

    // 1.3) Alternate Function & PCTL
    GPIOA->AFSEL |= (1 << UART0_RX_PIN);    // A0 Alternate Function aktivieren
    GPIOA->AFSEL |= (1 << UART0_TX_PIN);    // A1 Alternate Function aktivieren
    GPIOA->PCTL &= ~(0xF << 0);             // 4 Bits in PMC0 löschen
    GPIOA->PCTL &= ~(0xF << 4);             // 4 Bits in PMC1 löschen
    GPIOA->PCTL |= (0x1 << 0);              // PMC0 = 1
    GPIOA->PCTL |= (0x1 << 4);              // PMC1 = 1

    // 1.4) Drive strength
    GPIOA->DR2R |= (1 << UART0_RX_PIN);     // Drive strength von A0 = 2mA
    GPIOA->DR2R |= (1 << UART0_TX_PIN);     // Drive strength von A1 = 2mA

    // 1.5) Pull-Up / Pull-Down nicht benötigt

    // 1.6) Digital Enable
    GPIOA->DEN |= (1 << UART0_RX_PIN);      // A0: digital enable
    GPIOA->DEN |= (1 << UART0_TX_PIN);      // A1: digital enable

    // 1.7) GPIO Interrupts nicht benötigt

    // 1.8) LOCK nicht benötigt
}

void init_uart() {

    const double BRD = 16000000.0 / (115200.0 * 16.0);
    const int IBRD = (int) BRD;
    const double fraction = BRD - IBRD;
    const int FBRD = (int)(fraction * 64.0 + 0.5);
    SYSCTL->RCGCUART |= (1 << 0);
    while (!(SYSCTL->PRUART & (1 << 0))) {};

    UART0->CTL &= ~(1 << 0);    // UART ausschalten
    UART0->IBRD = IBRD;     
    UART0->FBRD = FBRD;
    UART0->LCRH = (0x3 << 5);   // 8 Bit, no Parity
    UART0->CC = 0;              // Taktquelle HSI
    UART0->CTL |= (1 << 0);     // UART anschalten
}

void _putchar(char c)
{
    // Warten, bis das Tx FIFO nicht mehr voll ist
    while (UART0->FR & (1 << 5)) {}

    // Wert in das Tx FIFO schreiben
    UART0->DR = c;
}

volatile uint32_t delay_counter = 0;

int delay(uint32_t val)
{
    delay_counter = val;
    while (delay_counter)
    {
        --delay_counter;
    }
}


/**
 * 7) Schreiben Sie nun die Funktion getchar() um Zeichen zu empfangen.
 *    Die Funktion soll prüfen, ob Daten im Datenregister vorhanden sind. 
 *    Ist dies der Fall sollen die Daten in received_char geschrieben werden 
 *    und die Funktion den Wert 1 zurückgeben.
 *    Sind keine Daten vorhanden soll die Funktion 0 zurückgeben.
 */
int getchar(char* received_char)
{
    if (UART0->FR & (1 << 4)) 
        return 0;

    *received_char = (UART0->DR & 0xFF);

    return 1;
}




void init_adc()
{

    /**********************************
     * ADC Modul initialisieren
     *********************************/
    // 1) Clock von ADC0 einschalten und warten bis bereit
    SYSCTL->RCGCADC |= (1 << 0);
    while (!(SYSCTL->PRADC & (1 << 0))) {}

    // 2) Clock des GPIO Moduls einschalten
   // SYSCTL->RCGCGPIO |= 0x01<<4; // Clock Port PE
    // Nicht notwendig für Temperatursensor

    // 3) GPIO Alternate Function
    //GPIOE->DIR &=~ (0x01<<0);
    //GPIOE->AFSEL |= (0x01<<0);
    // Nicht notwendig für Temperatursensor

    // 4) GPIO als Analog Pin konfigurieren (DEN)
      //GPIOE->DEN &=~ (0x01<<0);
    // Nicht notwendig für Temperatursensor

    // 5) Isolierungsschaltung deaktivieren GPIOAMSEL
      //GPIOE->AMSEL |= (0x01<<0);
    // Nicht notwendig für Temperatursensor

    // 6) Priorität der Sequenzer konfigurieren
    ADC0->SSPRI = 0;

    // 1 Msps
    ADC0->PC = 0x7;

    /*********************************
     * ADC Sequencer 0 initialisieren
     *********************************/
    // 1) Sequencer deaktivieren
    ADC0->ACTSS &= ~(1 << 0); //  ADC Active Sample Sequencer

    // 2) Trigger Event konfigurieren (Trigger durch Software)
    ADC0->EMUX = 0x0; // ADC Event Multiplexer Select

    // 3) ADC Trigger Quelle für PWM auswählen
    // Nur notwendig, falls PWM als trigger verwendet wird...

    // 4) Sample Quellen für alle Samples konfigurieren
    // ADC0->SSMUX0 |= 0x03; // MUX0 = 3 (AIN3)
    // Nicht notwendig, da Temperatursensor

    // 5) Sample Control bits für alle Samples konfigurieren
    // 4 x Sampling des Temperatursensors
    ADC0->SSCTL0 = (1 << 3) | (1 << 7) | (1 << 11) | (1 << 15); // ADC Sample Sequence Control 0

    // 5.1) END bit für das letzte Sample setzen
    ADC0->SSCTL0 |= (1 << 13); // ADC Sample Sequence Control 0

    // 6) Interrupts anschalten
    //    Nicht notwendig für diese Aufgabe

    // 7) Sequencer aktivieren
    ADC0->ACTSS |= (1 << 0); //  ADC Active Sample Sequencer

    /*********************************
     * ADC0 Averaging Circuit initialisieren
     *********************************/
    // Averager: 4x Überabtastung
    ADC0->SAC = 0x02;
}

void SysTick_Handler(void)
{
    if (delay_counter > 0)
    {
        delay_counter--;
    }

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
 * 8) Schreiben Sie nun die main() so um, dass 
 *    - jede Sekunde ein Zähler erhöht wird und der Zählerstand 
 *      mit printf ausgegeben wird
 *    - falls ein 'r' gedrückt wurde, soll der Zähler wieder auf 0
 *      zurückgesetzt werden
 */
int main()
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

    uint32_t counter = 0;
    uint8_t rcvbuffer;
   // adcByTimer_init();
    init_gpio();
    init_uart();
    init_systick();
    init_adc();

    while (1)
    {
        delay(1000);
        printf("Counter: %d\n", counter);
        counter++;
        if (getchar(&rcvbuffer)) {
            if (rcvbuffer = 'r') {
                counter = 0;
            }
        }
    

        /**
         * 3) Warten Sie hier in der Schleife darauf, dass 
         *    Daten im ADC Fifo von Sequencer 0 gelandet sind
         *    und der ADC nicht mehr BUSY ist
         */
        // Warten bis das FIFO nicht mehr leer ist (d.h. der ADC wurde
        // gestartet und es liegen schon Ergebnisse im FIFO)
        while (ADC0->SSFSTAT0 & (1 << 8)) {}

        // Warten bis der ADC nicht mehr aktiv ist
        while (ADC0->ACTSS & (1 << 16)) {}

        /** 
         * 4) Lesen Sie nun die Daten vom FIFO und berechnen
         *    Sie den Mittelwert
         */
        int adcValue = 0;
        for (int i = 0; i < 4; i++)
        {
            // Werte auslesen und gleich aufsummieren
           adcValue += ADC0->SSFIFO0;
        }
        adcValue = adcValue / 4;

        /**
         * 5) Berechnen Sie anhand der im Datenblatt gegebenen Formel
         *    und des in 4) berechneten Mittelwerts die aktuelle Temperatur 
         */
       float temperature = 147.5 - (75 * 3.3 * adcValue) / 4096.0;

        /** 
         * 6) Geben Sie die Temperatur mittels printf aus
         */
       printf("Temperatur: %f\n", temperature);
    }
}


