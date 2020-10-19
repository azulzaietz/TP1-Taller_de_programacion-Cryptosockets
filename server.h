#ifndef SERVER_H
#define SERVER_H

#include "common_socket.h"
#include "common_coder_selector.h"
#include "common_long_option_reader.h"
#define BUF_SIZE 64

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
    const char* server_port;
    const char* method;
    const char* key;
} server_t;

/* *****************************************************************
 *                PRIMITIVAS DEL SERVIDOR
 * *****************************************************************/
//Inicializa un servidor con los parametros correspondientes.
//Post: el servidor esta listo para ser usado y recibir
//mensajes.
void server_init(server_t* self, int argc, char* const* argv);

//Lee los parametros pasados por linea de comandos para
//inicializar el servidor.
void _read_command_line(server_t* self, int argc, char* const* argv);

//Recibe un mensaje cifrado del cliente y lo muestra 
//descifrado por salida estándar.
void receive_coded_message_from_client(server_t* self);

#endif
