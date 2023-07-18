#include "uart.h"
#include "TM4C123.h"

#define UART0_RX_PIN 0
#define UART0_TX_PIN 1
#define UARTx_TXFF 5
#define UARTx_RXFE 4

void init_uart_gpio()
{
    // 1.1) Clock aktivieren
    SYSCTL->RCGCGPIO |= (1 << 0); // Clock von GPIOA anschalten
    while (!(SYSCTL->PRGPIO & (1 << 0)))
    {
    } // Warten, bis das Modul bereit ist

    // 1.2) Richtung (Eingang/Ausgang) konfigurieren
    GPIOA->DIR &= ~(1 << UART0_RX_PIN); // A0 als Eingang konfigurieren (Rx)
    GPIOA->DIR |= (1 << UART0_TX_PIN);  // A1 als Ausgang konfigurieren (Tx)

    // 1.3) Alternate Function & PCTL
    GPIOA->AFSEL |= (1 << UART0_RX_PIN); // A0 Alternate Function aktivieren
    GPIOA->AFSEL |= (1 << UART0_TX_PIN); // A1 Alternate Function aktivieren
    GPIOA->PCTL &= ~(0xF << 0);          // 4 Bits in PMC0 löschen
    GPIOA->PCTL &= ~(0xF << 4);          // 4 Bits in PMC1 löschen
    GPIOA->PCTL |= (0x1 << 0);           // PMC0 = 1
    GPIOA->PCTL |= (0x1 << 4);           // PMC1 = 1

    // 1.4) Drive strength
    GPIOA->DR2R |= (1 << UART0_RX_PIN); // Drive strength von A0 = 2mA
    GPIOA->DR2R |= (1 << UART0_TX_PIN); // Drive strength von A1 = 2mA

    // 1.5) Pull-Up / Pull-Down nicht benötigt

    // 1.6) Digital Enable
    GPIOA->DEN |= (1 << UART0_RX_PIN); // A0: digital enable
    GPIOA->DEN |= (1 << UART0_TX_PIN); // A1: digital enable

    // 1.7) GPIO Interrupts nicht benötigt

    // 1.8) LOCK nicht benötigt
}

void init_uart()
{
    init_uart_gpio();

    const uint32_t BR = 115200;
    const uint32_t IBRD = 16000000 / (BR * 16);
    const uint32_t FBRD = (64 * 16000000 / (115200 * 16)) - (64 * IBRD);

    SYSCTL->RCGCUART |= (1 << 0);
    while (!(SYSCTL->PRUART & (1 << 0)))
    {
    };

    UART0->CTL &= ~(1 << 0); // UART ausschalten
    UART0->IBRD = IBRD;
    UART0->FBRD = FBRD;
    UART0->LCRH = (0x3 << 5); // 8 Bit, no Parity
    UART0->CC = 0;            // Taktquelle HSI
    UART0->CTL |= (1 << 0);   // UART anschalten
}

void _putchar(char c)
{
    // Warten, bis das Tx FIFO nicht mehr voll ist
    while (UART0->FR & (1 << 5))
    {
    }

    // Wert in das Tx FIFO schreiben
    UART0->DR = c;
}

int getchar(char *received_char)
{
    if (UART0->FR & (1 << 4))
        return 0;

    *received_char = (UART0->DR & 0xFF);

    return 1;
}
