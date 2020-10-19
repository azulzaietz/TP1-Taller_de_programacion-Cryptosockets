#ifndef CODER_SELECTOR_H
#define CODER_SELECTOR_H

#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_RC4.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
    const char* key;
    const char* method;
    void* coder;
    cesar_t* cesar;
    vigenere_t* vigenere;
    rc4_t* rc4;
} coder_selector_t;

/* *****************************************************************
 *                PRIMITIVAS DEL CODER SELECTOR
 * *****************************************************************/

//Inicializa el cifrador correspondiente
void coder_selector_init(coder_selector_t* self, const char* method,
const char* key, cesar_t* cesar, vigenere_t* vigenere,
rc4_t* rc4);

//Crea el cifrador que corresponde al metodo pasado por parametro
//en la inicializacion del selector.
void _select_coder_method(coder_selector_t* self);

//Cifra un mensaje con el cifrador correspondiente.
void code(coder_selector_t* self, unsigned char* buffer,
size_t read_bytes);

//Descifra un mensaje con el metodo correspondiente.
void decode(coder_selector_t* self, unsigned char* buffer,
size_t read_bytes);

#endif
