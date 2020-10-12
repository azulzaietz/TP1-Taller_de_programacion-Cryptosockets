#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
    unsigned char* key;
} vigenere_t;

/* *****************************************************************
 *                PRIMITIVAS DEL CIFRADO DE VIGENERE
 * *****************************************************************/

//Crea un cifrador de vigenere
//Post: devuelve un cifrador con la clave a utilizar para cifrar y descifrar
int create(vigenere_t* self, unsigned char* key);

//Libera la memoria reservada para el cifrador.
//Pre: el cifrador fue inicializado (creado)
//Post: se eliminan todos los elementos del cifrador, se libera la memoria reservada para el mismo.
void destroy(vigenere_t* cesar);

//Recibe un mensaje a cifrar como parámetro.
//Post: devuelve el mensaje cifrado
void code(vigenere_t* self, unsigned char *message, size_t read_bytes);

//Recibe un mensaje codificado
//Post: devuelve el mensaje descifrado (original).
void decode(vigenere_t* self, unsigned char* message, size_t read_bytes);