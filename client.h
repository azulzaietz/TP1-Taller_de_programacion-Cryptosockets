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

void init_client(client_t* self, int argc, char* const* argv);

void _read_command_line(client_t* self, int argc, char* const* argv);

void send_coded_message_to_server(client_t* self);

void uninit_client(client_t* self);
