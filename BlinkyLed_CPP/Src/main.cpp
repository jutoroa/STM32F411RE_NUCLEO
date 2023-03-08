// Programa en c++ para generar el blinky de un LED en el STM32F411RE


#include "mcal_reg.h"

#define RCC_AHB1ENR		(*((volatile unsigned int *) 0x40023830))
#define GPIOA_MODER		(*((volatile unsigned int *) 0x40020000))
#define GPIOA_ODR		(*((volatile unsigned int *) 0x40020014))

// Definimos una clase LED
class Led{
	// Una vez creada la clase tenemos que asignarle el Access specifier
	public:		// Everything under this specifier is accessable from other functions
		typedef std::uint32_t port_type;	// Tamaño del "puerto"/registros
		typedef std::uint32_t bval_type;	// Bits Value (numero del pin)

		// Creamos el constructor de la clase
		Led(const port_type p,bval_type b):port(p),bval(b){

			// Tenemos que asignar a la dirección de memoria, el valor
			// Manera en C: *((volatile uint32_t *)GPIOB) = (uint32_t) bval;
			/* Disable pin*/
			*reinterpret_cast<volatile port_type *>(port) &= ~(1U << bval);  // Desabilitar el pin

			/* Set pin mode to output */
			const port_type gpio_mode_reg = port - 0x14;
			*reinterpret_cast<volatile port_type *>(gpio_mode_reg) |= (1U << (bval * 2));

		}

		// Creamos una función toggle
		void toggle() const // La funcion tiene atributo const ya que no cambia los parámetros de la clase
		{
			*reinterpret_cast<volatile port_type *>(port) ^= (1U << bval);
		}

		void pseudoDelayMs(int n){
			int i;
			for(;n>0;n--){
				for(i=0;i<3200;i++){

				}
			}
		}

	// Atributos que solamente pueden ser accedidos por miembros de la clase
	private:
		const port_type port;
		const bval_type bval;

};



int main(void)
{
	RCC_AHB1ENR |= (1U<<0); /* Enable clock for GPIOA */

	Led led5(mcal::reg::gpioa,mcal::reg::gpioa_pin5);

	while(1){
		led5.toggle();
		led5.pseudoDelayMs(1000);
	}
}
