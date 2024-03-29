#ifndef VIGENERE_H
#define VIGENERE_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
    unsigned char* key;
    size_t len_key;
    int pos_key;
} vigenere_t;

/* *****************************************************************
 *                PRIMITIVAS DEL CIFRADO DE VIGENERE
 * *****************************************************************/

//Crea un cifrador de vigenere
//Post: devuelve un cifrador con la clave a utilizar para cifrar y descifrar
int vigenere_create(vigenere_t* self, const char* key);

//Recibe un mensaje a cifrar como parámetro.
//Post: devuelve el mensaje cifrado
void vigenere_code(vigenere_t* self, unsigned char *message, size_t read_bytes);

//Recibe un mensaje codificado
//Post: devuelve el mensaje descifrado (original).
void vigenere_decode(vigenere_t* self, unsigned char* message, 
    size_t read_bytes);

#endif
