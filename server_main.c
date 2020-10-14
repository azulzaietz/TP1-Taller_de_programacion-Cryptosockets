#include "common_socket.h"
#include "common_file_reader.h"

/*
1º) int socket ( int dominio, int tipo, int protocolo )  
          crea un socket sin nombre de un dominio, tipo y p 
rotocolo específico 
          dominio   : AF_INET, AF_UNIX 
          tipo      : SOCK__DGRAM, SOCK__STREAM 
          protocolo : 0 ( protocolo por defecto ) 

2º) int bind ( int dfServer, struct sockaddr* direccServer, int longDirecc ) 

          nombra un socket: asocia el socket no nombrado de descriptor dfServer con la dirección del socket almacenado en direccServer. La dirección depende de si estamos en un dominio AF_UNIX o AF_INET. 

3º) int listen ( int dfServer, int longCola ) 

          especifica el máximo número de peticiones de conexión pendientes. 

4º) int accept ( int dfServer, struct sockaddr* direccCliente, int* longDireccCli) 

          escucha al socket nombrado servidor dfServer y espera hasta que se reciba la petición de la conexión de un cliente. Al ocurrir esta incidencia, crea un socket sin nombre con las mismas características que el socket servidor original, lo conecta al socket cliente y devuelve 
un descriptor de fichero que puede ser utilizado para la comunicación con el cliente.
*/

int main(int argc, char const* argv[]) {

    socket_t socket;
	socket_t peer;
	char buffer[64];

    socket_bind_and_listen(&socket, NULL, argv[1]);

    socket_accept(&socket, &peer);
    socket_receive(&peer, buffer, 64);

    printf("Buffer recibido: %s\n", buffer);

    socket_uninit(&socket);

    return 0;
}