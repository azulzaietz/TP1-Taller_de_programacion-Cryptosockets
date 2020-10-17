#include "common_socket.h"
#include "common_file_coder.h"

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

void server_init(server_t* self, const char* server_port, const char* method, const char* key);

void receive_coded_message_from_client(server_t* self);

void _decode_message(server_t* self, unsigned char* buffer, ssize_t bytes_received, void* coder);

void server_uninit(server_t* self);
