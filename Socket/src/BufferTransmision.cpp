#include "BufferTransmision.h"
#include <cstring>

namespace Com {

BufferTransmision::BufferTransmision(size_t capacidad) {
	tamanio = 0;
	this->capacidad = capacidad;
	buffer = NULL;
	if (capacidad > 0) {
		buffer = new t_buffer[capacidad];
	}
}

BufferTransmision::BufferTransmision(const t_buffer* buffer, size_t tamanio) {
	this->tamanio = tamanio;
	this->capacidad = tamanio;
	this->buffer = NULL;
	if (tamanio > 0) {
		this->buffer = new t_buffer[tamanio];
		memcpy(this->buffer, buffer, tamanio);
	}
}

BufferTransmision::BufferTransmision(const BufferTransmision& aCopiar) {
	capacidad = aCopiar.capacidad;
	tamanio = aCopiar.tamanio;
	buffer = NULL;
	if (aCopiar.buffer != NULL) {
		buffer = new t_buffer[capacidad];
		memcpy(buffer, aCopiar.buffer, tamanio);
	}
}

void BufferTransmision::asignarBuffer(const t_buffer* buffer, size_t tamanio) {
	if (tamanio > this->capacidad) {
		if (this->buffer != NULL) {
			delete[] this->buffer;
		}
		this->buffer = new t_buffer[tamanio];
		this->capacidad = tamanio;
	}
	this->tamanio = tamanio;
	if (tamanio > 0) {
		memcpy(this->buffer, buffer, tamanio);
	}
}

void BufferTransmision::redimensionar(size_t nuevaCapacidad) {
	capacidad = nuevaCapacidad;
	if (capacidad <= 0) {
		tamanio = 0;
		if (buffer != NULL) {
			delete[] buffer;
		}
		buffer = NULL;
	}
	else {
		t_buffer *nuevo = new t_buffer[capacidad];

		/* Si la nueva capacidad es menor al tamanio ocupado actual, al
		 * achicarse el buffer se pierden datos y este queda lleno */
		if (tamanio > capacidad) {
			tamanio = capacidad;
		}

		memcpy(nuevo, buffer, tamanio);
		delete[] buffer;
		buffer = nuevo;
	}
}

bool BufferTransmision::insertarDatos(const void* dato, size_t tamanioDato) {
	if ((tamanio + tamanioDato) > capacidad) {
		return false;
	}
	memcpy(&buffer[tamanio], dato, tamanioDato);
	tamanio += tamanioDato;
	return true;
}

void BufferTransmision::vaciarBuffer() {
	tamanio = 0;
}

const BufferTransmision::t_buffer* BufferTransmision::obtenerBuffer() const {
	return buffer;
}

size_t BufferTransmision::obtenerBuffer(std::string &aEscribir) const {
	aEscribir.assign(buffer, tamanio);
	return tamanio;
}

bool BufferTransmision::obtenerByteBuffer(char &byte, size_t posicion) const {
	if (posicion >= tamanio) {
		return false;
	}
	byte = buffer[posicion];
	return true;
}

size_t BufferTransmision::getTamanioOcupado() const {
	return tamanio;
}

size_t BufferTransmision::getCapacidadTotal() const {
	return capacidad;
}

size_t BufferTransmision::getCapacidadRestante() const {
	return (capacidad - tamanio);
}

bool BufferTransmision::estaLleno() const {
	return (capacidad == tamanio);
}

BufferTransmision::~BufferTransmision() {
	if (buffer != NULL) {
		delete[] buffer;
	}
}
}
