#include "common_socket.h"
#include "common_file_coder.h"
#include "common_long_option_reader.h"

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

//Descifra el mensaje recibido.
void _decode_message(server_t* self, unsigned char* buffer, 
    ssize_t bytes_received, void* coder);

