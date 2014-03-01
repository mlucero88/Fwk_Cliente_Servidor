#ifndef BUFFERTRANSMISION_H
#define	BUFFERTRANSMISION_H

#include <string>

namespace Com {

/**
 * @brief Clase contenedora para poder insertar datos de cualquier tipo
 * primitivo, u objetos de cualquier clase, en un buffer, insertando
 * siempre al final. Se utiliza para enviar y recibir datos por un socket
 */

class BufferTransmision {
public:

	/**
	 * @brief Tipo de dato primitivo que utiliza la clase para almacenar datos
	 */
	typedef char t_buffer;

	/**
	 * @brief Construye un BufferTransmision con capacidad @a capacidad
	 * @param capacidad Capacidad del buffer, en bytes
	 */
	explicit BufferTransmision(size_t capacidad);

	/**
	 * @brief Construye un BufferTransmision a partir de una copia de los datos
	 * apuntados por @a buffer, cuyo tamaño es @a tamanio. La capacidad del
	 * objeto creado es @a tamanio
	 * @param buffer Puntero a los datos que se guardarán en la instancia
	 * creada
	 * @param tamanio Tamaño total de los datos apuntados por @a buffer en bytes
	 */
	BufferTransmision(const t_buffer* buffer, size_t tamanio);

	/**
	 * @brief Constuctor copia
	 * @param aCopiar Instancia a copiar
	 */
	BufferTransmision(const BufferTransmision& aCopiar);

	/**
	 * @brief Método que elimina el contenido previo y le asigna una copia de
	 * los datos apuntados por @a buffer, cuyo tamaño es @a tamanio. La
	 * capacidad del objeto será @a tamanio si su capacidad previa era menor a
	 * @a tamanio, o se mantendrá con la misma capacidad si era mayor o igual
	 * @param buffer Puntero a los datos que se guardarán en la instancia
	 * @param tamanio Tamaño total de los datos apuntados por @ buffer en bytes
	 */
	void asignarBuffer(const t_buffer* buffer, size_t tamanio);

	/**
	 * @brief Método para redimensionar la capacidad del buffer. Los datos se
	 * conservan. En caso de que @a nuevaCapacidad sea menor al tamaño ocupado
	 * en el buffer, el buffer queda en estado lleno y los datos que quedaron
	 * afuera de la capacidad se pierden
	 * @param nuevaCapacidad Tamaño nuevo del buffer
	 */
	void redimensionar(size_t nuevaCapacidad);

	/**
	 * @brief Método para insertar datos al final del buffer (es decir, desde
	 * la última posición en donde se escribió), si el buffer tiene capacidad
	 * libre igual o mayor a @a tamanioDato
	 * @param dato Puntero a los datos a insertar
	 * @param tamanioDato Tamaño de los datos a insertar
	 * @return <tt>true</tt> en caso de éxito
	 * @return <tt>false</tt> si @a tamanioDato es mayor a la capacidad libre
	 * del buffer
	 */
	bool insertarDatos(const void* dato, size_t tamanioDato);

	/**
	 * @brief Método que vacía los datos del buffer
	 */
	void vaciarBuffer();

	/**
	 * @brief Método que obtiene el buffer para consulta, no modificación
	 * @return Puntero a los datos guardados en el buffer
	 */
	const t_buffer* obtenerBuffer() const;

	/**
	 * @brief Método para obtener una copia del contenido entero del buffer.
	 * El contenido se guarda en @a aEscribir (cualquier contenido previo
	 * se descarta)
	 * @note Esto no implica que los bytes deban ser interpretados como
	 * caracteres; simplemente se decide usar este contenedor ya que permite
	 * muchas operaciones útiles sobre los bytes que contiene
	 * @param aEscribir Contenedor string a guardar la copia de los datos
	 * @return El tamaño total de los datos guardados en el contenedor
	 */
	size_t obtenerBuffer(std::string &aEscribir) const;

	/**
	 * @brief Método que retorna el byte corresponiente a la posición
	 * @a posicion del buffer. Las posiciones comienzan en el índice 0
	 * @param byte Variable donde se guardará el byte solicitado
	 * @param posicion Posición del byte solicitado
	 * @return <tt>true</tt> en caso de éxito
	 * @return <tt>false</tt> si @a posicion es una posición inválida
	 */
	bool obtenerByteBuffer(char &byte, size_t posicion) const;

	/**
	 * @brief Método para obtener el tamaño ocupado
	 * @return El tamaño ocupado, en bytes
	 */
	size_t getTamanioOcupado() const;

	/**
	 * @brief Método para obtener la capacidad máxima
	 * @return La capacidad máxima, en bytes
	 */
	size_t getCapacidadTotal() const;

	/**
	 * @brief Método para obtener la capacidad restante
	 * @return La capacidad restante, en bytes
	 */

	size_t getCapacidadRestante() const;

	/**
	 * @brief Método para consultar si el buffer está lleno
	 * @return <tt>true</tt> si el buffer está lleno
	 */
	bool estaLleno() const;

	/**
	 * @brief Destructor
	 */
	~BufferTransmision();

private:

	t_buffer *buffer;
	size_t capacidad, tamanio;
};
}

#endif
