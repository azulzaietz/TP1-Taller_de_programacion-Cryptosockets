#include "common_socket.h"
#include "common_file_coder.h"

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
    const char* server_port;
} server_t;

/* *****************************************************************
 *                PRIMITIVAS DEL SERVIDOR
 * *****************************************************************/

void server_init(server_t* self, const char* server_port);

void receive_coded_message_from_client(server_t* self);

void server_uninit(server_t* self);