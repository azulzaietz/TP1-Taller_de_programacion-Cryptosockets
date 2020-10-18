#include "common_coder_selector.h"
#include "common_socket.h"
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

typedef struct {
    FILE* fp;
} file_coder_t;

/* *****************************************************************
 *                PRIMITIVAS DEL FILE CODER
 * *****************************************************************/

//Inicializa el cifrador de archivo con el nombre del archivo 
//pasado por parámetro. Abre el archivo en caso de ser necesario
//deja el file_coder listo para cifrar un archivo.
int file_coder_init(file_coder_t* self, const char* file_name);

//Cifra el archivo con el que previamente fue inicializado con el
//metodo pasado por parametro y lo envía al socket indicado por
//parametro.
int code_file(file_coder_t* self, socket_t* socket, 
        void* coder, const char* method);

//Cierra el archivo abierto en la inicializacion en caso de 
//ser necesario.
int file_coder_uninit(file_coder_t* self);

