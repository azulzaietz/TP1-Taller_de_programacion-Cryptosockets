#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_RC4.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define BUF_SIZE 64

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef void (*file_coder_callback_t)(char *chunk, size_t chunk_size, void *callback_ctx);

typedef struct {
    FILE* fp;
    void* coder;
} file_coder_t;

/* *****************************************************************
 *                PRIMITIVAS DEL FILE CODER
 * *****************************************************************/

int file_coder_init(file_coder_t* self, const char* file_name, const char* method, const char* key);

void (*coder_t) (void* coder, unsigned char* message, size_t length);
void _init_coder_method(file_coder_t* self, const char* method, const char* key);

int code_file(file_coder_t* self, file_coder_callback_t callback, void* callback_ctx);

int file_coder_uninit(file_coder_t* self);