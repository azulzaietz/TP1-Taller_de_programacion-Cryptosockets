#include "common_socket.h"
#include "common_file_reader.h"

/*
1º) int socket ( int dominio, int tipo, int protocolo )  

          crea un socket sin nombre de un dominio, tipo y protocolo específico 
          dominio   : AF_INET, AF_UNIX 
          tipo      : SOCK__DGRAM, SOCK__STREAM 
          protocolo : 0 ( protocolo por defecto ) 

2º) int connect ( int dfCliente, struct sockaddr* direccServer, int longDirecc ) 

          intenta conectar con un socket servidor cuya dirección 
          se encuentra incluida en la estructura apuntada por direccServer. 
          El descriptor dfCliente se utilizará para comunicar con el socket servidor. 
          El tipo de estructura dependerá del dominio en que nos encontremos. 
*/

static void _send_chunk(char *chunk, size_t chunk_size, void *callback_ctx) {
	socket_t *socket = callback_ctx;
	socket_send(socket, chunk, chunk_size);
}

int main(int argc, char const* argv[]) {

    socket_t socket;
    socket_connect(&socket, argv[1], argv[2]);

    file_reader_t file_reader;
    file_open(&file_reader, NULL);

    read_file(&file_reader, _send_chunk, &socket);

    file_close(&file_reader);
    socket_uninit(&socket);

    return 0;
}