/*
 * uartDriver.h
 *
 *  Created on: 22/03/2023
 *      Author: Emmanuel
 */

#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_

/* Función para inicializar el uart2 en modo RXTX */
void uart2Init(void);

/* Función para leer por UART2 */
char uart2Read(void);

/* Función para escribir por UART */
int uart2Write(char ch);

#endif /* UARTDRIVER_H_ */
