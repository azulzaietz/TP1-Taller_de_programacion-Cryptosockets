#include "server.h"

void server_init(server_t* self, const char* server_port) {
    self->server_port = server_port;
}

void receive_coded_message_from_client(server_t* self) {

    socket_t socket;
	socket_t peer;
	char buffer[BUF_SIZE];

    socket_bind_and_listen(&socket, NULL, self->server_port);

    socket_accept(&socket, &peer);

    ssize_t sr = 0;

    while ((sr = socket_receive(&peer, buffer, BUF_SIZE)) != 0) {
        fwrite(buffer, sizeof(char), sr, stdout);
    }

    socket_uninit(&socket);
}