#ifndef RC4_H
#define RC4_H

#include <stdio.h>
#include <string.h>

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
    unsigned char state_vector[256];
    unsigned char i;
    unsigned char j;
} rc4_t;

/* *****************************************************************
 *                PRIMITIVAS DEL CIFRADO RC4
 * *****************************************************************/

//Crea un cifrador RC4
//Post: devuelve un cifrador con la clave a utilizar para cifrar y descifrar
int rc4_create(rc4_t* self, const char* key);

//Recibe un mensaje a cifrar como parámetro.
//Post: devuelve el mensaje cifrado
//Sirve tambien para descifrar un mensaje cifrado con rc4
void rc4_code(rc4_t* self, unsigned char *message, size_t read_bytes);

#endif
