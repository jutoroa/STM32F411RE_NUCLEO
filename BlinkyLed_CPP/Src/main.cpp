// Programa en c++ para generar el blinky de un LED en el STM32F411RE


#include <stdint.h>

// Definimos una clase LED

class Led{
	// Una vez creada la clase tenemos que asignarle el Access specifier
	public:		// Everything under this specifier is accessable from other functions
		typedef uint32_t port_type;	// Tamaño del "puerto"/registros
		typedef uint32_t bval_type;	// Bits Value (numero del pin)

		// Creamos el constructor de la clase
		Led(const port_type p,bval_type b):port(p),bval(b){

			// Tenemos que asignar a la dirección de memoria, el valor
			// Manera en C: *((volatile uint32_t *)GPIOB) = (uint32_t) bval;
			*reinterpret_cast<volatile port_type *>(port) &= ~(1U << bval);  // Desabilitar el pin

			port_initial value =

		}

	// Atributos que solamente pueden ser accedidos por miembros de la clase
	private:
		const port_type port;
		const bval_type bval;

};



int main(void)
{

}
