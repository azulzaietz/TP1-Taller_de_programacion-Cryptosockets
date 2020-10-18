#include "common_socket.h"
#include "common_file_coder.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

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

void server_init(server_t* self, const char* server_port, 
    int argc, char* const* argv);

void receive_coded_message_from_client(server_t* self);

void _decode_message(server_t* self, unsigned char* buffer, 
    ssize_t bytes_received, void* coder);

void server_uninit(server_t* self);

void _read_command_line(server_t* self, int argc, char* const* argv);
