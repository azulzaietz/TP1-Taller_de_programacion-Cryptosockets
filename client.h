#ifndef CLIENT_H
#define CLIENT_H

#include "common_file_coder.h"
#include "common_coder_selector.h"
#include "common_socket.h"
#include "common_long_option_reader.h"

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
    const char* server_host;
    const char* server_port;
    const char* method;
    const char* key;
} client_t;

/* *****************************************************************
 *                PRIMITIVAS DEL CLIENTE
 * *****************************************************************/

//Lee los parametros de la linea de comandos para inicializar
//los atributos del cliente.
//Pre: todos los parametros fueron pasados correctamente
//Post: el cliente queda listo para ser usado y enviar mensajes.
void init_client(client_t* self, int argc, char* const* argv);

//Envia el mensaje correspondiente al servidor al que esta conectado.
void send_coded_message_to_server(client_t* self);

#endif
