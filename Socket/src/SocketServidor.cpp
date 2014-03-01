#include "SocketServidor.h"
#include "SocketCliente.h"

#define ERROR_ENLACE -1
#define ERROR_ESCUCHA -1
#define ERROR_ACEPTACION -1

namespace Com {

SocketServidor::SocketServidor(in_port_t puerto, int protocolo) throw () :
		SocketTCP_IP(protocolo) {
	direccion.setPuerto(puerto);
	direccion.setDireccionIP(INADDR_ANY );
}

SocketServidor::SocketServidor(const SocketServidor &servidor) throw () :
		SocketTCP_IP(servidor.protocolo) {
	direccion = servidor.direccion;
	sockfd = servidor.sockfd;
}

void SocketServidor::enlazarServidor() throw (EnlaceExcepcion) {
//    int yes=1;
//    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));

	int resultadoEnlace = bind(sockfd, direccion.getDireccion(),
			sizeof(struct sockaddr));
	if (resultadoEnlace == ERROR_ENLACE) {
		throw EnlaceExcepcion(strerror(errno));
	}
}

void SocketServidor::escucharClientes(int colaMaxima) throw (EscuchaExcepcion) {
	int resultadoEscucha = listen(sockfd, colaMaxima);
	if (resultadoEscucha == ERROR_ESCUCHA) {
		throw EscuchaExcepcion(strerror(errno));
	}
}

SocketCliente* SocketServidor::aceptarClientes() throw (AceptacionExcepcion) {
	struct sockaddr address;
	socklen_t tamanio = sizeof(struct sockaddr);
	t_socket nuevoSocket = accept(sockfd, &address, &tamanio);

	if (nuevoSocket == ERROR_ACEPTACION) {
		throw AceptacionExcepcion(strerror(errno));
	}
	SocketCliente *nuevoCliente = new SocketCliente(nuevoSocket, address,
			protocolo);
	return nuevoCliente;
}

SocketServidor::~SocketServidor() {
}
}
