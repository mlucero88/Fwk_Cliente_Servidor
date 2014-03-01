#ifndef SOCKETEXCEPCION_H_
#define SOCKETEXCEPCION_H_

#include "ComunicacionExcepcion.h"

namespace Com {

/**
 * @brief Clase que define una excepción de un socket. Se utiliza para tener
 * una jerarquía de excepciones para la clase Socket
 */

class SocketExcepcion: public ComunicacionExcepcion {
public:

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 */
	explicit SocketExcepcion(const char *motivo) throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~SocketExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();
};
}

#endif
