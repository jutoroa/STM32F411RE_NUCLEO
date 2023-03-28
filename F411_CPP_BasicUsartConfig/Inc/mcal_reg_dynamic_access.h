/*
 * mcal_reg_dynamic_acces.h
 *
 *  Created on: 20/03/2023
 *      Author: Emmanuel
 */

#ifndef MCAL_REG_DYNAMIC_ACCESS_H_
#define MCAL_REG_DYNAMIC_ACCESS_H_

namespace mcal{
	namespace reg{

		/* Creación del template */
		template <typename 	regAddressType,
				  typename 	regValueType>

		/* Creación de la clase que usará el template */
		class regDynamicAccess{

		public:

			/* Modificación de un registro COMPLETO */
			static void regSet(regAddressType address, regValueType value){

				// Se cambian todos los bits del registro
				*reinterpret_cast <volatile regAddressType *> (address) = static_cast <regValueType> (value);
			}

			/* Modificación tipo "OR" de un registro */
			static void regOr(regAddressType address, regValueType value){

				// Se ponen en 1 los bits seleccionados sin cambiar los demás
				*reinterpret_cast <volatile regAddressType *> (address) |= static_cast <regValueType> (value);
			}

			/* Modificación tipo "AND" de un registro */
			static void regAnd(regAddressType address, regValueType value){

				// Los bits del registro que sean iguales al valor, se ponen en 1, los otros en 0
				*reinterpret_cast <volatile regAddressType *> (address) &= static_cast <regValueType> (value);
			}

			/* Modificación tipo "AND" y "NOT" de un registro */
			static void regNot(regAddressType address, regValueType value){

				// Se ponen en 0 los bits seleccionados sin cambiar los demás
				*reinterpret_cast <volatile regAddressType *> (address) &= static_cast <regValueType> (~value);
			}

			/* Función que retorna el valor de un registro */
			static regAddressType regGet(regAddressType address){

				// Se retorna el valor en el registro de la dirección específica
				return *reinterpret_cast <volatile regAddressType *> (address);
			}

			/* Modificación (en 1) de un bit específico */
			static void setBit(regAddressType address, regValueType value){

				// Se pone en 1 el bit deseado
				*reinterpret_cast <volatile regAddressType *> (address) |= static_cast <regValueType> (1U << value);
			}

			/* Modificación (en 0) de un bit específico */
			static void clearBit(regAddressType address, regValueType value){

				// Se pone en 0 el bit deseado
				*reinterpret_cast <volatile regAddressType *> (address) &= static_cast <regValueType>(~ static_cast <regValueType> (1U << value));
			}

			/* Niega el valor de un bit específico */
			static void toggleBit(regAddressType address, regValueType value){

				// Se intercambia el valor del bit deseado
				*reinterpret_cast <volatile regAddressType *> (address) ^= static_cast <regValueType> (1U << value);
			}

			/* Función que retorna el valor de un bit en un registro específico */
			static bool bitGet(regAddressType address, regValueType value){

				// Se ponen todos los bits en 0, menos el de la posición deseada, luego se revisa si es 1 o 0.
				return (regGet(address) & (static_cast <regValueType> (1U << value) != static_cast <regValueType> (0U)));
			}
		};
	}
}

#endif /* MCAL_REG_DYNAMIC_ACCESS_H_ */
