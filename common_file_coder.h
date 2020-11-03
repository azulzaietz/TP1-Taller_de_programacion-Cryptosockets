#ifndef FILE_CODER_H
#define FILE_CODER_H

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

//Recibe un coder_selector que cifra el archivo con el 
//metodo correspondiente y lo envía con el socket indicado por
//parametro.
//Pre: se inicializaron un socket, un coder selector y un
//file coder.
//Post: el archivo indicado en la inicializacion del file_coder
//fue cifrado y enviado.
int code_file(file_coder_t* self, socket_t* socket, 
    coder_selector_t* coder_selector, const char* method);

//Cierra el archivo abierto en la inicializacion en caso de 
//ser necesario.
int file_coder_uninit(file_coder_t* self);

#endif
