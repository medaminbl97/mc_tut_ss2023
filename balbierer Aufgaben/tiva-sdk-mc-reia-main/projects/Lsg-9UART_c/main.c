//#include "TM4C123GH6PM.H"
#include "printf.h"

#include <stdint.h>
#include <stdbool.h>

/* Driverlib includes */
#include "inc/hw_memmap.h"

#include "gpio.h"
#include "uart.h"
#include <stdint.h>
#include <string.h>

#define UART0_RX_PIN        0
#define UART0_TX_PIN        1
#define UARTx_TXFF          5
#define UARTx_RXFE          4

// Pufferspeicher für Transmit und Receive
char txBuffer[128];
char rxBuffer[128];

volatile uint32_t delay_counter = 0;








void listenCallback(uint32_t numOfBytes) 
{	
	 if ((numOfBytes > 9) && (strncmp(rxBuffer, "SetRedLed", 9) == 0)) 
		{			
				gpiof_setPin(1, 1);
		}	
		else if ((numOfBytes > 11) && (strncmp(rxBuffer, "ResetRedLed", 11) == 0)) 
		{			
				gpiof_setPin(1, 0);
		}	
		else if ((numOfBytes > 10) && (strncmp(rxBuffer, "SetBlueLed", 10) == 0)) 
		{			
		
				gpiof_setPin(2, 1);
		}
        else if ((numOfBytes > 12) && (strncmp(rxBuffer, "ResetBlueLed", 12) == 0)) 
		{			
		
				gpiof_setPin(2, 0);
		}
		/* Ansonsten Echo zurückschicken */
		else 
		{
				size_t bytesToWrite = snprintf(txBuffer, sizeof(txBuffer), "uC: %.*s\r\n", numOfBytes-1, rxBuffer);
				uart_send(txBuffer, bytesToWrite);
		}
		
		/* Erneut auf eingehende Daten warten */
		uart_listen(rxBuffer, sizeof(rxBuffer), listenCallback);
}


void leftSwitchPressed(void)
{	
	
		
size_t bytesToWrite;
   
	gpiof_ICR(4); 
		if(gpiof_readPin(4))
		{	gpiof_setPin(1, 0);
			 bytesToWrite = snprintf(txBuffer, sizeof(txBuffer), "Left Button is released!\r\n");		
		}
		else
		{       gpiof_setPin(1, 1);
			bytesToWrite = snprintf(txBuffer, sizeof(txBuffer), "Left Button is pressed!\r\n");
		}
		
		uart_send(txBuffer, bytesToWrite);	
}


void rightSwitchPressed(void)
{
		size_t bytesToWrite = 0;
	
		gpiof_ICR(0);


		if(gpiof_readPin(0))
		{
                gpiof_setPin(2, 0); //deactivate LED
				bytesToWrite = snprintf(txBuffer, sizeof(txBuffer), "Right Button is released!\n");
		}
		else
		{       gpiof_setPin(2, 1); 
				bytesToWrite = snprintf(txBuffer, sizeof(txBuffer), "Right Button is pressed!\n");
		}
		 
		uart_send(txBuffer, bytesToWrite);
}






int main()
{
   /* Initialisierung der einzelnen Baugruppen */
		gpiof_configureInputPin(0);
		gpiof_configureInputPin(4);
		gpiof_configureOutputPin(1);
		gpiof_configureOutputPin(2);
		gpiof_configureOutputPin(3);
	
		/* ISR-Funktionen übergeben */
		activateGpiofEdgeInterrupts(4, leftSwitchPressed);	
		activateGpiofEdgeInterrupts(0, rightSwitchPressed);
	
	
	
		/* UART initialisieren */
		uart_init();		

		
		/* Erstmalig auf eingehende Daten warten */
        uart_listen(rxBuffer, sizeof(rxBuffer), listenCallback);

    while (1)
    {

    
    }

}




