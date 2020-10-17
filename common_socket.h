#ifndef SOCKET_H
#define SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <netdb.h>
#include <errno.h>

#define FAMILY AF_INET
#define PROTOCOL 0
#define SOCK_TYPE SOCK_STREAM
#define SERVER_FLAGS AI_PASSIVE
#define CLIENT_FLAGS 0

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
    int fd;
} socket_t;

/* *****************************************************************
 *                PRIMITIVAS DEL SOCKET
 * *****************************************************************/

//Inicializa un socket con su file descriptor asociado.
void socket_init(socket_t* self, int fd);

//Cierra el socket.
//Pre: se inicializó un socket.
//Post: cierra el socket.
void socket_uninit(socket_t* self);

//Devuelve una lista de posibles direcciones para conectarse.
struct addrinfo* _get_addrinfo(socket_t* self, const char* host, const char* service, int flags);

//Devuelve true si pudo conectarse a un puerto y activarse para recibir conexiones,
//false en caso de error.
bool socket_bind_and_listen(socket_t* self, const char* host, const char* service);

//Acepta una conexion y devuelve el fd en caso exitoso, -1 en caso de error.
int socket_accept(socket_t* listener, socket_t* peer);

//Devuelve true si la conexión fue exitosa, false en caso de error.
bool socket_connect(socket_t* self, const char* host, const char* service);

//Devuelve la cantidad de bytes enviados o -1 si ocurrió un error.
ssize_t socket_send(socket_t* self, unsigned char* buffer, size_t length);

//Devuelve la cantidad de bytes recibidos o -1 si ocurrió un error.
ssize_t socket_receive(socket_t* self, unsigned char* buffer, size_t length);

#endif