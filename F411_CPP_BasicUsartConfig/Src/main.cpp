/**
 ******************************************************************************
 * @file           : main.cpp
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "uartDriver.h"
#include "stdio.h"
#include "cstdio"
//#include <iostream> // Para utilizar cout. Consume muchos recursos (funciona)

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/* ----------------------- Pasos a seguir ---------------------
 * 1. Una vez se tenga listo el driver del USART, buscar en Google lo siguiente:
 * Redefining low-level library functions to enable direct use of high-level library functions in the C library
 *
 * Abrir la opción por parte de ARM, se cuenta con 2 opciones: Realizar el
 * retargeting para cout (C++), y para printf(C, pero igual funciona en C++).
 *
 * 2. Copiar y pegar el código que presentan como plantilla (en la página de arm)
 * en el driver del USART y modificar las funciones fgetc() y fputc().
 *
 * 3. Si lo que se busca es utilizar cout, se debe incrementar el heap size para poder
 * que quepa todo el código base necesario para utilizar cout. Esto se hace en el archivo
 * STM32F411RETX_FLASH.ld,  cambiando el valor de _Min_Heap_Size (normalmente es 0x200) en
 * 0x2000.
 *
 * 4. Para poder imprimir los caracteres con printf, es necesario redefinir
 * ya sea la función __write() o la función __io_putchar que se encuentran
 * en el archivo syscalls.
 *
 * NOTA: Si se desean imprimir flotantes con printf, es necesario activar la
 * opción desde MCU settings.
 * -------------------------------------------------------------- */


/* ---
 * Para poder imprimir los caracteres con printf, es necesario
 * redefinir ya sea la función __write() o la función __io_putchar.
 * De modo que el caracter sea enviado por el USART, la LCD o lo que
 * se requiera.
 * --- */
extern "C"{
int __io_putchar(int ch){

	// Se envía el caracter por USART2
	uart2Write((char)ch);
	return ch;
}
}

/** @program : Transmisión por UART2 usando printf **/
int main(void)
{
	// Inicialización del uart2
	uart2Init();

	/* Prueba del printf en el mensaje de bienvenida */
	printf("- - - Hola desde C++ usando printf() - - -\n\r");
//	std::cout<<"Hola desde C++ usando cout"<<std::endl; // Para esto se debe incluir <iostream>

	/* Ciclo infinito */
	while(1){

		// Para probar el uso de enteros
		int prueba = 200;
		printf("Probando probando, Uno dos, uno %d, \n\r", prueba);
		for(int i = 0; i<1800000; i++){};

		// Variable auxiliar para probar si el RX funciona
//		char tecla = uart2Read();
//		if(tecla == 's'){
//			printf("Soy la letra s\n\r");
//		}
	}
}
