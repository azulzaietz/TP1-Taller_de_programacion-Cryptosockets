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
int create(rc4_t* self, unsigned char* key);

//Genera vector de entrada para el flujo de cifrado.
//Vector de 256 elementos con todos los números del 0 al 255 y luego los
//desordena a partir de la clave secreta compartida por emisor y receptor.
void _create_state_vector(unsigned char* key, unsigned char* s);

//Intercambia el valor de dos posiciones del vector entre sí.
void _swap(unsigned char* vector, int pos1, int pos2);

//Recibe un mensaje a cifrar como parámetro.
//Post: devuelve el mensaje cifrado
void code(rc4_t* self, unsigned char *message, size_t read_bytes);

//Recibe un mensaje codificado
//Post: devuelve el mensaje descifrado (original).
void decode(rc4_t* self, unsigned char* message, size_t read_bytes);