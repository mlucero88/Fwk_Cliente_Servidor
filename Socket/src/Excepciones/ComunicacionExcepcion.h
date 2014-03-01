#ifndef COMUNICACIONEXCEPCION_H_
#define COMUNICACIONEXCEPCION_H_

#include <exception>
#include <string>

namespace Com {

/**
 * @brief Clase que define una excepción en una comunicación
 */

class ComunicacionExcepcion: public std::exception {
public:

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 */
	explicit ComunicacionExcepcion(const char *motivo) throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~ComunicacionExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();

protected:

	/**
	 * @brief Texto descriptivo del error
	 */
	std::string motivo;
};
}

#endif
