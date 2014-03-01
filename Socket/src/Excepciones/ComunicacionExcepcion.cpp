#include "ComunicacionExcepcion.h"

namespace Com {

ComunicacionExcepcion::ComunicacionExcepcion(const char *motivo) throw() {
	this->motivo.assign(motivo);
}

ComunicacionExcepcion::~ComunicacionExcepcion() throw() {}

const char* ComunicacionExcepcion::what() const throw() {
	std::string error("ERROR EN LA COMUNICACION! Motivo: ");
	error.append(motivo);
	return error.c_str();
}
}
