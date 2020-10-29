#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_RC4.h"

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;
} encryptor_t;

/* *****************************************************************
 *                PRIMITIVAS DEL CODER SELECTOR
 * *****************************************************************/

cesar_t* get_cesar(encryptor_t* self);
vigenere_t* get_vigenere(encryptor_t* self);
rc4_t* get_rc4(encryptor_t* self);

#endif
