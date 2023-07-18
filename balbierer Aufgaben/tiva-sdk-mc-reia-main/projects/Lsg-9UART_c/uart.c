
#include "uart.h"
#include "TM4C123GH6PM.h"


// Variables for Transmission
char* transmitPtr = 0;
int numOfBytesTx = 0;


// Variables for Reception
char* receivePtr = 0; 
int receiveBufferSize = 0;
int numOfBytesRx = 0;

callbackHandlerType rxCallback = 0;


void uart_init()
{

		/* Clocks für die Baugruppe UART0 
		 * und die Baugruppe GPIOA einschalten */
		SYSCTL->RCGCGPIO	|= 0x01<<0;
	   SYSCTL->RCGCUART |= (1 << 0);
   	 while (!(SYSCTL->PRUART & (1 << 0))) {};

		/* Kofigurieren der Baugruppe GPIOA */
		GPIOA->AFSEL			|= (0x01<<0 | 0x01<<1);
		GPIOA->DEN				|= (0x01<<0 | 0x01<<1);
		GPIOA->PCTL				&= ~(0x0F<<0 | 0x0F<<4);
		GPIOA->PCTL				|= (0x01<<0 | 0x01<<4);

		/* Kofigurieren der Baugruppe UART0 */
	
	const double BRD = 16000000.0 / (115200.0 * 16.0);
    const int IBRD = (int) BRD;
    const double fraction = BRD - IBRD;
    const int FBRD = (int)(fraction * 64.0 + 0.5);
 

    UART0->CTL &= ~(1 << 0);    // UART ausschalten
    UART0->IBRD = IBRD;     
    UART0->FBRD = FBRD;
    UART0->LCRH = (0x3 << 5);   // 8 Bit, no Parity
    UART0->CC = 0;              // Taktquelle HSI
    UART0->CTL |= (1 << 0);     // UART anschalten
	/* Transmit und Receive Interrupt einstellen */
		UART0->IM					|= (0x01<<5 | 0x01<<4);
		
		/* Im NVIC UART0 Interrupt aktivieren */
		NVIC->ISER[0]			|= 0x01<<5;	
		
		/* UART0 Baugruppe einschalten (Transmit und Receive Funktion sollen ausgeschaltet bleiben!) */
		UART0->CTL				 = (UART0->CTL & ~(0x03<<8)) | (0x01<<0);
}


void uart_send(char* message, uint8_t messageLengh)
{
	/* Setzen der Transmit Variablen */
	transmitPtr = message;
	numOfBytesTx = messageLengh + 1;
	
	/* UART TX Leitung einschalten */
	UART0->CTL	|= 0x01<<8;
	
	/* Erstes Byte schreiben
	 * Nach Erfolgreichem Senden wird der UART0 Handler aufgerufen */
	transmitPtr++;
	numOfBytesTx--;
	UART0->DR		 = *(transmitPtr-1);
}


void uart_listen(char* buffer, uint8_t bufferSize, callbackHandlerType callbackHanlder)
{
	/* Setzen der Variablen */
	receivePtr = buffer;
	receiveBufferSize = bufferSize;
	rxCallback = callbackHanlder;
	numOfBytesRx = 0;
	
	/* UART Receive Funktion aktivieren */
	UART0->CTL	|= 0x01<<9;
	
	// Der Rest wird in der ISR gemacht...
}


int getchar(char* received_char)
{
    if (UART0->FR & (1 << 4)) 
        return 0;

    *received_char = (UART0->DR & 0xFF);

    return 1;
}

void _putchar(char c)
{
    // Warten, bis das Tx FIFO nicht mehr voll ist
    while (UART0->FR & (1 << 5)) {}

    // Wert in das Tx FIFO schreiben
    UART0->DR = c;
}



void UART0_Handler(void)
{
		/* Abfrage ob Transmit FIFO leer ist (Eine Nachricht wurde gesendet) */
		if (UART0->MIS & 0x01<<5) 
		{
				/* Löschen des 'Transmit FIFO empty' Interrupts */
				UART0->ICR	|= 0x01<<5;
			
				if (numOfBytesTx > 1) 
				{
					// Nächstes Byte schreiben
					UART0->DR 	 	 = *(transmitPtr);
					numOfBytesTx--;
					transmitPtr++;
				}
				else if (numOfBytesTx == 1)
				{
					numOfBytesTx--;
				}
				else 
				{
					// Alle Bytes gesendet, Transmit disable
					UART0->CTL 	 &= ~(0x01<<8);
				}
		}
		
		/* Abfrage ob Receive FIFO voll ist (Eine Nachricht wurde empfangen) */
		if (UART0->MIS & 0x01<<4) 
		{
				/* Löschen des 'Receive FIFO full' Interrupts */
				UART0->ICR	|= 0x01<<4;
				
				/* Abfrage ob der RxBuffer noch Platz für ein weiteres Bytes hat */
				if (numOfBytesRx < receiveBufferSize - 1) 
				{
						/* Lesen des nächsten Bytes */
						*(receivePtr) = (char)(UART0->DR & 0xFF);
						/* Variable für Anzahl der Bytes im Buffer erhöhen */
						numOfBytesRx++;
						
						/* Wenn das Symbol für Ende des ASCII String empfangen wurde, lesen beenden */
						if (*(receivePtr) == '\r')
						{
								/* Lesen beenden */
								UART0->CTL 	 &= ~(0x01<<9);
								
								/* Callback ausführen */
								if (rxCallback != 0) 
								{
									rxCallback(numOfBytesRx);
								}
						}
						else 
						{
								receivePtr++;
						}
				}
				else 
				{
						/* Letzes Byte lesen */
						*(receivePtr) = (char)(UART0->DR & 0xFF);
						numOfBytesRx++;
						
						/* Receive disable, um Buffer overflow zu vermeiden */
						UART0->CTL 	 &= ~(0x01<<9);
						
						/* Callback ausführen */
						if (rxCallback != 0) 
						{
								rxCallback(numOfBytesRx);
						}
				}
		}
}
