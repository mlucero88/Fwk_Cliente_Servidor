#include "SocketExcepcion.h"

namespace Com {

SocketExcepcion::SocketExcepcion(const char *motivo) throw () :
		ComunicacionExcepcion(motivo) {
	this->motivo.assign(motivo);
}

SocketExcepcion::~SocketExcepcion() throw () {
}

const char* SocketExcepcion::what() const throw () {
	std::string error("ERROR EN LA OPERACION DE SOCKET! Motivo: ");
	error.append(motivo);
	return error.c_str();
}
}
