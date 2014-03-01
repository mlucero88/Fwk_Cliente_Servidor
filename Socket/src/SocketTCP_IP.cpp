#include "SocketTCP_IP.h"

#define FLAGS 0
#define ERROR_ENVIO -1
#define ERROR_RECEPCION -1
#define USUARIO_DESCONECTADO 0
#define TEMP_BUFFER_SIZE 512

namespace Com {

SocketTCP_IP::SocketTCP_IP(int protocolo) throw () :
		Socket(AF_INET, SOCK_STREAM, protocolo) {
	direccion.setFamilia(AF_INET);
}

SocketTCP_IP::SocketTCP_IP(const struct sockaddr &dir, int protocolo) throw () :
		Socket(AF_INET, SOCK_STREAM, protocolo, dir) {
}

SocketTCP_IP::SocketTCP_IP(const SocketTCP_IP &socket) throw () :
		Socket(socket.tipo, socket.tipo, socket.protocolo) {
	direccion = socket.direccion;
	sockfd = socket.sockfd;
}

in_port_t SocketTCP_IP::getPuerto() const throw () {
	return direccion.getPuerto();
}

std::string SocketTCP_IP::getDireccionIP() const throw () {
	std::string str;
	direccion.getDireccionIP(str);
	return str;
}

ssize_t SocketTCP_IP::enviar(const BufferTransmision &buffer)
		throw (EnvioExcepcion) {
	ssize_t bytesEnviados;
	bytesEnviados = send(sockfd, buffer.obtenerBuffer(),
			buffer.getTamanioOcupado(), FLAGS);

	if (bytesEnviados == ERROR_ENVIO) {
		throw EnvioExcepcion(strerror(errno));
	}
	return bytesEnviados;
}

ssize_t SocketTCP_IP::recibir(BufferTransmision &buffer)
		throw (RecepcionExcepcion) {
	ssize_t bytesRecibidos;
	BufferTransmision::t_buffer *tempBuffer =
			new BufferTransmision::t_buffer[buffer.getCapacidadTotal()];
	bytesRecibidos = recv(sockfd, tempBuffer, buffer.getCapacidadTotal(),
			FLAGS);

	if (bytesRecibidos > 0) {
		buffer.asignarBuffer(tempBuffer, bytesRecibidos);
	}
	delete[] tempBuffer;

	if (bytesRecibidos == ERROR_RECEPCION) {
		throw RecepcionExcepcion(strerror(errno),
				RecepcionExcepcion::error_recepcion);
	}
	if (bytesRecibidos == USUARIO_DESCONECTADO) {
		throw RecepcionExcepcion(strerror(errno),
				RecepcionExcepcion::usuario_desconectado);
	}
	return bytesRecibidos;
}

size_t SocketTCP_IP::enviarConProtocolo(const BufferTransmision &buffer)
		throw (EnvioExcepcion) {
	size_t bytesAenviar;
	ssize_t resultadoEnvio;
	size_t bytesTotalesEnviados = 0;
	const BufferTransmision::t_buffer* tempBuffer;

	/* Primero envio el tamanio del buffer que voy a enviar */
	size_t tamanioBuffer = buffer.getTamanioOcupado();
	bytesAenviar = sizeof(tamanioBuffer);
	tempBuffer = (BufferTransmision::t_buffer*) &tamanioBuffer;

	while (bytesAenviar != 0) {
		resultadoEnvio = send(sockfd, tempBuffer, bytesAenviar, FLAGS);
		if (resultadoEnvio == ERROR_ENVIO) {
			throw EnvioExcepcion(strerror(errno));
		}
		bytesAenviar -= resultadoEnvio;
		tempBuffer += resultadoEnvio;
		bytesTotalesEnviados += resultadoEnvio;
	}

	/* Envio el contenido del buffer */
	bytesAenviar = buffer.getTamanioOcupado();
	tempBuffer = buffer.obtenerBuffer();

	while (bytesAenviar != 0) {
		resultadoEnvio = send(sockfd, tempBuffer, bytesAenviar, FLAGS);
		if (resultadoEnvio == ERROR_ENVIO) {
			throw EnvioExcepcion(strerror(errno));
		}
		tempBuffer += resultadoEnvio;
		bytesAenviar -= resultadoEnvio;
		bytesTotalesEnviados += resultadoEnvio;
	}
	return bytesTotalesEnviados;
}

size_t SocketTCP_IP::recibirConProtocolo(BufferTransmision &buffer)
		throw (RecepcionExcepcion) {
	size_t bytesArecibir;
	size_t tamanioBuffer;
	ssize_t resultadoRecepcion;
	size_t bytesTotalesRecibidos = 0;

	/* Debo utilizar un buffer temporal ya que no puedo escribir directamente
	 * sobre mi objeto BufferTransmision */
	BufferTransmision::t_buffer tempBuffer[TEMP_BUFFER_SIZE];

	/* Primero recibo la cantidad de bytes que me enviaron */
	bytesArecibir = sizeof(tamanioBuffer);

	while (bytesArecibir != 0) {
		resultadoRecepcion = recv(sockfd, &tempBuffer[bytesTotalesRecibidos],
				bytesArecibir, FLAGS);

		if (resultadoRecepcion == ERROR_RECEPCION) {
			throw RecepcionExcepcion(strerror(errno),
					RecepcionExcepcion::error_recepcion);
		}
		if (resultadoRecepcion == USUARIO_DESCONECTADO) {
			throw RecepcionExcepcion(strerror(errno),
					RecepcionExcepcion::usuario_desconectado);
		}

		bytesArecibir -= resultadoRecepcion;
		bytesTotalesRecibidos += resultadoRecepcion;
	}
	memcpy(&tamanioBuffer, tempBuffer, sizeof(tamanioBuffer));

	/* Recibo los bytes. Primero verifico que pueda almacenar la cantidad total
	 * de bytes en mi buffer */
	bytesArecibir = tamanioBuffer;
	buffer.vaciarBuffer();
	if (bytesArecibir > buffer.getCapacidadTotal()) {
		buffer.redimensionar(tamanioBuffer);
	}

	while (bytesArecibir != 0) {
		resultadoRecepcion = recv(sockfd, tempBuffer, TEMP_BUFFER_SIZE, FLAGS);

		if (resultadoRecepcion == ERROR_RECEPCION) {
			throw RecepcionExcepcion(strerror(errno),
					RecepcionExcepcion::error_recepcion);
		}
		if (resultadoRecepcion == USUARIO_DESCONECTADO) {
			throw RecepcionExcepcion(strerror(errno),
					RecepcionExcepcion::usuario_desconectado);
		}

		buffer.insertarDatos((void*) tempBuffer, resultadoRecepcion);
		bytesArecibir -= resultadoRecepcion;
		bytesTotalesRecibidos += resultadoRecepcion;
	}

	return bytesTotalesRecibidos;
}

SocketTCP_IP::~SocketTCP_IP() {
}
}
