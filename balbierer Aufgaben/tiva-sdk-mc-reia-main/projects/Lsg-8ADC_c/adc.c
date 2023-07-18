#include "adc.h"
#include "TM4C123GH6PM.h"

float temperature = -1.00;

void adcByTimer_init(void)
{
//ADC0 Initialisierung

	SYSCTL->RCGCADC 	|= 0x01<<0;			//Clock für ADC0 Modul aktivieren
	
	ADC0->ACTSS 			&= ~(0x01<<0);	//ADC ausschalten bevor verändernungen vorgenommen werden
	ADC0->EMUX 				|= 0x05<<0;			//Timer als triggerquelle auswählen
	ADC0->SSMUX0 			|= 0x03<<0;			//Ain3 Pin als als erstes Sample im SampleSequencer0 auswählen
	ADC0->SSCTL0			|= 0x01<<7;			//Interner Temperatur Sensor als zweites Sample im SampleSequencer0 auswählen
	ADC0->SSCTL0 			|= 0x01<<5;			//Im Sample Sequencer 0 ist das zweite Sample (Temperatur Sensor) das letzte
																		//-> Danach wird das Samplen abgebrochen und die Umwandlung ist beendet
	ADC0->SSCTL0			|= 0x01<<6;			//Interrupt wird nach dem zweiten Sample ausgelöst
	ADC0->IM					|= 0x01<<0;			//Interrupt für Sample Sequenzer 0 demaskieren (aktivieren)
	NVIC->ISER[0]			|= 0x01<<14;		//Im NVIC Interrupt für Sample Sequenzer 0 aktivieren
																		//->ADC0SS0_Handler wird nach dem Beenden des zweiten Samples aufgerufen

	ADC0->ACTSS 			|= 0x01<<0;			//ADC wieder einschalten	
	
//Timer0A Initialisierung
	SYSCTL->RCGCTIMER |= 0x01<<0;			//Clock für Timer0 aktivieren
	
	TIMER0->CTL 			&= ~(0x01<<0);	//Timer ausschalten
	
	TIMER0->CTL 			|= 0x01<<5;			//Timer als Trigger für ADC Modul	
	TIMER0->CFG 			= 0;						//Timer art auswählen (32 Bit Timer)	
	TIMER0->TAMR 			|= 0x02<<0;			//Timer Mode: periodic Timer	
	TIMER0->TAILR 		= 50e6;					//Timer Match Value setzen (50 Mio -> 1Hz bei 50 MHz Takt)
	
	TIMER0->CTL 			|= 0x01<<0;			//Timer wieder einschalten	
}

void ADC0Seq1_Handler(void)	
{
	//Aus dem FIFO den nächsten Wert in eine Temperatur umwandlen und in die Variable temperature speichern
	temperature 			= (147.5 - (75*3.3*ADC0->SSFIFO0)/4096); 

	
	//Den Interrupt für ADC0SS0 wieder aktivieren
	ADC0->ISC					|= 0x01<<0; 		
}
