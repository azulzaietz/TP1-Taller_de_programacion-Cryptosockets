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
 *                PRIMITIVAS DEL ENCRYPTOR
 * *****************************************************************/

//Devuelve un puntero a un cifrador del metodo de cesar
cesar_t* get_cesar(encryptor_t* self);

//Devuelve un puntero a un cifrador del metodo de vigenere
vigenere_t* get_vigenere(encryptor_t* self);

//Devuelve un puntero a un cifrador del metodo rc4
rc4_t* get_rc4(encryptor_t* self);

#endif
