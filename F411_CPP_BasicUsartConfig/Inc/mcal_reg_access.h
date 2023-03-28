/*
 * mcal_reg_access.h
 *
 *  Created on: 20/03/2023
 *      Author: Emmanuel
 */

#ifndef MCAL_REG_ACCESS_H_
#define MCAL_REG_ACCESS_H_

namespace mcal{
	namespace reg{

		/* Creación del template */
		template <typename 	addrType,
				  typename 	regType,
				  const		addrType addr,		// Dirección en memoria
				  const		regType val>		// Posición del bit

		/* Creación de la clase que usará el template */
		class regAccess{

		public:

			/* Modificación de un registro COMPLETO */
			static void regSet(){

				// Se cambian todos los bits del registro
				*reinterpret_cast <volatile addrType *> (addr) = static_cast <regType> (val);
			}

			/* Modificación tipo "OR" de un registro */
			static void regOr(){

				// Se ponen en 1 los bits seleccionados sin cambiar los demás
				*reinterpret_cast <volatile addrType *> (addr) |= static_cast <regType> (val);
			}

			/* Modificación tipo "AND" de un registro */
			static void regAnd(){

				// Los bits del registro que sean iguales al valor, se ponen en 1, los otros en 0
				*reinterpret_cast <volatile addrType *> (addr) &= static_cast <regType> (val);
			}

			/* Modificación tipo "AND" y "NOT" de un registro */
			static void regNot(){

				// Se ponen en 0 los bits seleccionados sin cambiar los demás
				*reinterpret_cast <volatile addrType *> (addr) &= static_cast <regType> (~val);
			}

			/* Función que retorna el valor de un registro */
			static regType regGet(){

				// Se retorna el valor en el registro de la dirección específica
				return *reinterpret_cast <volatile addrType *> (addr);
			}

			/* Modificación (en 1) de un bit específico */
			static void setBit(){

				// Se pone en 1 el bit deseado
				*reinterpret_cast <volatile addrType *> (addr) |= static_cast <regType> (1U << val);
			}

			/* Modificación (en 0) de un bit específico */
			static void clearBit(){

				// Se pone en 0 el bit deseado
				*reinterpret_cast <volatile addrType *> (addr) &= static_cast <regType> (~ static_cast <regType> (1U << val));
			}

			/* Niega el valor de un bit específico */
			static void toggleBit(){

				// Se intercambia el valor del bit deseado
				*reinterpret_cast <volatile addrType *> (addr) ^= static_cast <regType> (1U << val);
			}

			/* Función que retorna el valor de un bit en un registro específico */
			static bool bitGet(){

				// Se ponen todos los bits en 0, menos el de la posición deseada, luego se revisa si es 1 o 0.
				return (regGet(addr) & (static_cast <regType> (1U << val) != static_cast <regType> (0U)));
			}
		};
	}
}


#endif /* MCAL_REG_ACCESS_H_ */
