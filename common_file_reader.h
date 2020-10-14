#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define BUF_SIZE 64

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct {
    FILE* fp;
} file_reader_t;

/* *****************************************************************
 *                PRIMITIVAS DEL FILE READER
 * *****************************************************************/

typedef void (*file_reader_callback_t)(char *chunk, size_t chunk_size, void *callback_ctx);

//Recibe un file_reader_t y el nombre de un archivo a leer o NULL en caso de que se quiera
//leer por stdin
//Post: devuelve 0 en caso exitoso, -1 si no se pudo abrir el archivo deseado.
int file_open(file_reader_t* self, const char* file_name);

//Cierra el archivo abierto previamente con init (si no se leyó de entrada estándar)
//Post: devuelve 0 en caso exitoso, -1 si hubo algún error al cerrar el archivo.
int file_close(file_reader_t* self);

//Lee el archivo completo que se abrió en init
int read_file(file_reader_t* self, file_reader_callback_t callback, void* callback_ctx);