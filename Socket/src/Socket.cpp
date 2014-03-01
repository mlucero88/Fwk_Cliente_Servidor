#include "Socket.h"
#include <cerrno>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "BufferTransmision.h"
#include "ExcepcionesSocket.h"

#define ERROR_CREACION -1
#define ERROR_CIERRE -1

namespace Com {

/* METODOS DE SOCKETADDRESS */

Socket::SocketAddress::SocketAddress() {
	memset(&direccion, 0, sizeof(direccion));
}

Socket::SocketAddress::SocketAddress(const struct sockaddr &direccion) {
	this->direccion = direccion;
}

Socket::SocketAddress::SocketAddress(const SocketAddress& aCopiar) {
	direccion = aCopiar.direccion;
}

const Socket::SocketAddress& Socket::SocketAddress::operator=(
		const SocketAddress &aAsignar) {
	direccion = aAsignar.direccion;
	return *this;
}

void Socket::SocketAddress::setFamilia(sa_family_t familia) {
	sockaddr_in *addr = (sockaddr_in*) &direccion;
	addr->sin_family = familia;
}

void Socket::SocketAddress::setPuerto(in_port_t puerto) {
	sockaddr_in *addr = (sockaddr_in*) &direccion;
	addr->sin_port = htons(puerto);
}

bool Socket::SocketAddress::setDireccionIP(const char* dirIP) {
	in_addr_t dir = inet_addr(dirIP);
	if (dir == (in_addr_t) -1) {
		return false;
	}
	sockaddr_in *addr = (sockaddr_in*) &direccion;
	addr->sin_addr.s_addr = dir;
	return true;
}

void Socket::SocketAddress::setDireccionIP(in_addr_t dirIP) {
	sockaddr_in *addr = (sockaddr_in*) &direccion;
	addr->sin_addr.s_addr = htonl(dirIP);
}

bool Socket::SocketAddress::setDireccionIPconDNS(const char *dirDNS) {
	struct hostent *he;
	he = gethostbyname(dirDNS);
	if (he == NULL) {
		return false;
	}
	sockaddr_in *addr = (sockaddr_in*) &direccion;
	addr->sin_addr = *((struct in_addr*) he->h_addr);
	return true;
}

in_port_t Socket::SocketAddress::getPuerto() const {
	return ntohs(((sockaddr_in*) &direccion)->sin_port);
}

void Socket::SocketAddress::getDireccionIP(std::string &aGuardarIP) const {
	aGuardarIP = inet_ntoa(((sockaddr_in*) &direccion)->sin_addr);
}

const struct sockaddr* Socket::SocketAddress::getDireccion() const {
	return &direccion;
}

Socket::SocketAddress::~SocketAddress() {
}

/* METODOS DE SOCKET */

Socket::Socket(int dominio, int tipo, int protocolo) throw () {
	this->dominio = dominio;
	this->tipo = tipo;
	this->protocolo = protocolo;
	sockfd = -1;
}

Socket::Socket(int dominio, int tipo, int protocolo,
		const struct sockaddr &dir) throw () :	direccion(dir) {
	this->dominio = dominio;
	this->tipo = tipo;
	this->protocolo = protocolo;
	sockfd = -1;
}

Socket::Socket(const Socket& aCopiar) throw () {
	direccion = aCopiar.direccion;
	sockfd = aCopiar.sockfd;
	protocolo = aCopiar.protocolo;
	dominio = aCopiar.dominio;
	tipo = aCopiar.tipo;
}

void Socket::crear() throw (CreacionExcepcion) {
	sockfd = socket(dominio, tipo, protocolo);
	if (sockfd == ERROR_CREACION) {
		throw CreacionExcepcion(strerror(errno));
	}
}

void Socket::cortarComunicacion(t_sentido_corte sentido) throw (
		CierreExcepcion) {
	if (shutdown(sockfd, sentido) == ERROR_CIERRE) {
		throw CierreExcepcion(strerror(errno));
	}
}

void Socket::cerrar() throw (CierreExcepcion) {
	if (close(sockfd) == ERROR_CIERRE) {
		throw CierreExcepcion(strerror(errno));
	}
}

Socket::~Socket() {
}
}
