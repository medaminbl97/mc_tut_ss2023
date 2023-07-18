#ifndef UART_H
#define UART_H

#include <stdint.h>

typedef void (*callbackHandlerType)(uint32_t numOfBytes);


void uart_init();

void uart_send(char* message, uint8_t messageLengh);
void uart_listen(char* buffer, uint8_t bufferSize, callbackHandlerType callbackHanlder);
int getchar(char* received_char);
void _putchar(char c);
#endif
