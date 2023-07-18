#ifndef UART_H_
#define UART_H_

/**
 * @brief Initialisiert UART0 (Virtual Com Part)
 *        mit 8N1, 115200. Konfiguriert auch die 
 *        zugehörigen Pins.
 */
void init_uart();

/**
 * @brief Wartet bis der UART bereit ist und sendet
 *        dann einen Buchstaben 
 * @param c Zu sendendes Zeichen
 * @return none
 */
void _putchar(char c);

/**
 * @brief Prüft ob ein Zeichen empfangen wurde und schreibt
 *        das Zeichen in received_char
 * @param received_char Hier wird das empfangene Zeichen rein-
 *                      geschrieben
 * @return 0, falls kein Zeichen vorhanden ist, ansonsten 1
 */
int getchar(char *received_char);

#endif /* UART_H_ */