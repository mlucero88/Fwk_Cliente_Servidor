#ifndef SOCKETTCPIP_H
#define	SOCKETTCPIP_H

#include "Socket.h"

namespace Com {

/**
 * @brief Clase que define el comportamiento en común de un socket TCP_IP, sea
 * cliente o servidor
 */

class SocketTCP_IP: public Socket {
public:

	/**
	 * @brief Método para obtener el puerto al que se está conectado (en caso
	 * de ser un SocketCliente) o su propio puerto (si es un SocketServidor)
	 * @return El número de puerto de la conexión
	 */
	virtual in_port_t getPuerto() const throw ();

	/**
	 * @brief Método para obtener la IP a la que se está conectado (en caso
	 * de ser un SocketCliente) o su propia IP (si es un SocketServidor)
	 * @return Un string con el número de IP, campos separados con '.'
	 */
	virtual std::string getDireccionIP() const throw ();

	/**
	 * @brief Método para enviar datos a través del socket. Puede no enviar
	 * el buffer completo en un solo llamado
	 * @pre Conexión establecida mediante SocketCliente::conectar (por parte
	 * del cliente) y SocketServidor::aceptar (por parte del servidor)
	 * @param buffer Contenedor con los datos a enviar
	 * @return La cantidad de bytes enviados
	 * @throw EnvioExcepcion Error generado al enviar datos
	 */
	virtual ssize_t enviar(const BufferTransmision &buffer)
			throw (EnvioExcepcion);

	/**
	 * @brief Método para recibir datos a través del socket. Puede no recibir
	 * todos los bytes que se le enviaron en un solo llamado. Si no hay datos
	 * para recibir, se bloquea la ejecución hasta recibir datos o se corte
	 * la comunicación con Socket::cortarComunicacion
	 * @pre Conexión establecida mediante SocketCliente::conectar (por parte
	 * del cliente) y SocketServidor::aceptar (por parte del servidor)
	 * @param buffer Contenedor donde se guardarán los datos recibidos. El
	 * contenido previo es descartado
	 * @return La cantidad de bytes recibidos
	 * @throw RecepcionExcepcion Error generado al recibir datos
	 */
	virtual ssize_t recibir(BufferTransmision &buffer)
			throw (RecepcionExcepcion);

	/**
	 * @brief Método para enviar datos. Utiliza un protocolo por defecto,
	 * que consiste en adjuntar al principio del envío el tamaño del
	 * buffer a enviar, en bytes. Cuando se recibe, se verifica la cantidad
	 * de bytes que se deben recibir, y no se retorna del método hasta que
	 * se reciba el mensaje completo, a menos que se arroje una excepción.
	 * @pre Conexión establecida mediante SocketCliente::conectar (por parte
	 * del cliente) y SocketServidor::aceptar (por parte del servidor)
	 * @param buffer Contenedor con los datos a enviar (no incluye el dato
	 * de control con el tamaño del buffer a enviar)
	 * @return La cantidad de bytes enviados, incluyendo dato de control con
	 * el tamaño del buffer a enviar
	 * @note No testeado
	 */
	virtual size_t enviarConProtocolo(const BufferTransmision &buffer)
			throw (EnvioExcepcion);

	/**
	 * @brief Método para recibir datos. Utiliza un protocolo por defecto,
	 * que consiste en adjuntar al principio del envío el tamaño del
	 * buffer a enviar, en bytes. Cuando se recibe, se verifica la cantidad
	 * de bytes que se deben recibir, y no se retorna del método hasta que
	 * se reciba el mensaje completo, a menos que se arroje una excepción.
	 * @pre Conexión establecida mediante SocketCliente::conectar (por parte
	 * del cliente) y SocketServidor::aceptar (por parte del servidor)
	 * @param buffer Contenedor donde se guardarán los datos recibidos. El
	 * contenido previo es descartado
	 * @return La cantidad de bytes recibidos, incluyendo dato de control con
	 * el tamaño del buffer a recibir
	 * @note No testeado
	 */
	virtual size_t recibirConProtocolo(BufferTransmision &buffer)
			throw (RecepcionExcepcion);

	/**
	 * @brief Destructor
	 */
	virtual ~SocketTCP_IP();

protected:

	/**
	 * @brief Constructor
	 * @param protocolo Protocolo del socket, comúnmente 0
	 */
	explicit SocketTCP_IP(int protocolo) throw ();

	/**
	 * @brief Constructor
	 * @param dir Estructura con la configuración de la dirección del socket
	 * @param protocolo Protocolo del socket, comúnmente 0
	 */
	SocketTCP_IP(const struct sockaddr &dir, int protocolo) throw ();

	/**
	 * Constructor copia
	 * @param socket SocketTCP_IP a copiar
	 */
	SocketTCP_IP(const SocketTCP_IP &socket) throw ();
};
}

#endif
