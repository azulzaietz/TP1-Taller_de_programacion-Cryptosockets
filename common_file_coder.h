#include "common_coder_selector.h"
#include "common_socket.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define BUF_SIZE 64

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

//typedef void (*file_coder_callback_t)(char *chunk, size_t chunk_size, void *callback_ctx);

typedef struct {
    FILE* fp;
    coder_selector_t* coder_selector;
} file_coder_t;

/* *****************************************************************
 *                PRIMITIVAS DEL FILE CODER
 * *****************************************************************/

int file_coder_init(file_coder_t* self, const char* file_name, coder_selector_t* coder);

void _init_coder_method(file_coder_t* self, const char* method, const char* key);

int code_file(file_coder_t* self, socket_t* socket);

int file_coder_uninit(file_coder_t* self);