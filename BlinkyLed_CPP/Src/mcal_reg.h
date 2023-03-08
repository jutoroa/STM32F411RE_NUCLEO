/*
 * mcal_reg.h
 *
 *  Created on: 8/03/2023
 *      Author: Juan Pablo
 */

#ifndef MCAL_REG_H_
#define MCAL_REG_H_

#include <cstdint>

namespace mcal{
	namespace reg{

		const std::uint32_t gpioa = 0x40020014;
		const std::uint32_t gpioa_pin5 = 5;
	}

}



#endif /* MCAL_REG_H_ */
