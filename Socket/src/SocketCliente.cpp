#include "SocketCliente.h"

#define ERROR_CONEXION -1

namespace Com {

SocketCliente::SocketCliente(in_port_t puertoDestino, in_addr_t dirIPdestino,
		int protocolo) throw () : SocketTCP_IP(protocolo) {
	direccion.setPuerto(puertoDestino);
	direccion.setDireccionIP(dirIPdestino);
}

SocketCliente::SocketCliente(in_port_t puertoDestino, const char *dirIPdestino,
		int protocolo) throw () : SocketTCP_IP(protocolo) {
	direccion.setPuerto(puertoDestino);
	direccion.setDireccionIP(dirIPdestino);
}

SocketCliente::SocketCliente(in_port_t puertoDestino,
		const std::string &dirDNSdestino, int protocolo) throw () :
		SocketTCP_IP(protocolo) {
	direccion.setPuerto(puertoDestino);
	direccion.setDireccionIPconDNS(dirDNSdestino.c_str());
}

SocketCliente::SocketCliente(t_socket socket, const struct sockaddr &dir,
		int protocolo) throw () : SocketTCP_IP(dir, protocolo) {
	sockfd = socket;
}

SocketCliente::SocketCliente(const SocketCliente &cliente) throw () :
		SocketTCP_IP(cliente.protocolo) {
	direccion = cliente.direccion;
	sockfd = cliente.sockfd;
}

void SocketCliente::conectar() throw (ConexionExcepcion) {
	int resultadoConectar = connect(sockfd, direccion.getDireccion(),
			sizeof(struct sockaddr));
	if (resultadoConectar == ERROR_CONEXION) {
		throw ConexionExcepcion(strerror(errno));
	}
}

SocketCliente::~SocketCliente() {
}
}
