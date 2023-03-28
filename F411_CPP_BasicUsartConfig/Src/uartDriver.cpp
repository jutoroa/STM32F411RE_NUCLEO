/*
 * uartDriver.cpp
 *
 *  Created on: 22/03/2023
 *      Author: Emmanuel
 */

#include "uartDriver.h"
#include "mcal_reg.h"
#include <stdio.h>

/* ---
 * Buscar en Google:
 * Redefining low-level library functions to enable direct use of high-level library functions in the C library
 *
 * Importante --> Retargeting cout
 *  --- */

/** Función para inicializar el UART2 */
void uart2Init(void){

	/* Habilitar el GPIOA */
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::ahb1enr, (1U << 0)>::regOr();

	/* Habilitar el USART */
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::apb1enr, (1U << 17)>::regOr();

	/* Configurar el PA2 como USART TX */
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::gpioa_moder, (0U << 4)>::regOr();
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::gpioa_moder, (1U << 5)>::regOr();

	/* Configurar el PA3 como USART RX */
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::gpioa_moder, (0U << 6)>::regOr();
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::gpioa_moder, (1U << 7)>::regOr();

	/* Habilitar TX RX, palabra de 8 bits */
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::uart2_cr1, (0x00C)>::regSet();

	/* Configurar TX RX como función alternativa */
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::gpioa_afrl, (0x7700)>::regOr();

	/* Configurar el baudrate a 9600 @ 16 MHz */
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::uart2_brr, (0x0683)>::regSet();

	/* Configurar 1 bit de parada */
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::uart2_cr2, (0x000)>::regSet();

	/* Deshabilitar el flow control */
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::uart2_cr3, (0x000)>::regSet();

	/* Habilitar el USART */
	mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::uart2_cr1, (0x2000)>::regOr();
}

/* Función para leer por UART2 */
char uart2Read(void){

	// Variable para almacenar el valor leído
	char receivedChar;

	/* Se espera hasta que llegue un caracter */
	while(!(mcal::reg::UART2->SR & 0x0020)){}

	// Se lee el caracter recibido
	receivedChar = mcal::reg::regAccess<std::uint32_t, std::uint32_t, mcal::reg::uart2_dr, 0U>::regGet();

	// Se retorna el caracter leído
	return receivedChar;
}

/* Función para escribir por UART2 */
int uart2Write(char ch){

	// Variable auxiliar
	std::uint32_t _ch = ch & 0xFF;

	// Se espera hasta que el buffer TX esté vacío
	while(!(mcal::reg::UART2->SR & 0x0080)){}
	mcal::reg::regDynamicAccess<std::uint32_t, std::uint32_t>::regSet(mcal::reg::uart2_dr, _ch);

	return 1;
}


/* --- Ejemplo de arm --- */
namespace std {
  struct __FILE
  {
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
  };

  FILE __stdout;
  FILE __stdin;
  FILE __stderr;

  /* --- Esta función se modifica. Básicamente lee el caracter --- */
  int fgetc(FILE *f)
  {
	  /* Your implementation of fgetc(). */

	  /* --- Acá empieza el código propio --- */
	  // Variable auxiliar
	  char c;

	  // Se lee el caracter recibido
	  c = uart2Read();

	  // Se evalúa si hay un 'carriage return' para agregar un salto de línea
	  if(c == '\r'){

		  // Se envía el carriage return
		  uart2Write(c);
		  c = '\n';
	  }

	  // Se hace un eco
	  uart2Write(c);

	  // Se retorna el caracter (antes era 0).
	  return (int)c;
	  /* --- Acá termina el código propio --- */
  }

  /* ---
   * Nota: Tener cuidado con la 'endianess' de fputc(). Esta toma un parámetro int
   * pero solo contiene un caracter. Para saber si el caracter se ubica al inicio
   * o al final de la palabra entera, se puede utilizar un código que está en
   * la página de arm.
   --- */
  int fputc(int c, FILE *stream)
  {
	  /* Your implementation of fputc(). */
	  /* --- Acá empieza el código propio --- */
	  return uart2Write((char)c);
  }

  int ferror(FILE *stream)
  {
    /* Your implementation of ferror(). */
	  return 0;
  }
  long int ftell(FILE *stream)
  {
    /* Your implementation of ftell(). */
	  return 0;
  }
  int fclose(FILE *f)
  {
    /* Your implementation of fclose(). */
    return 0;
  }
  int fseek(FILE *f, long nPos, int nMode)
  {
    /* Your implementation of fseek(). */
    return 0;
  }
  int fflush(FILE *f)
  {
    /* Your implementation of fflush(). */
    return 0;
  }
}
