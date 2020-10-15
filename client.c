#include "client.h"

static void _send_chunk(char *chunk, size_t chunk_size, void *callback_ctx) {
	socket_t *socket = callback_ctx;
	socket_send(socket, chunk, chunk_size);
}

void init_client(client_t* self, const char* server_host, const char* server_port, const char* method, const char* key) {
    self->server_host = server_host;
    self->server_port = server_port;
    self->method = method;
    self->key = (unsigned char*) key;
}

void send_coded_message_to_server(client_t* self) {
    
    socket_t socket;
    socket_connect(&socket, self->server_host, self->server_port);

    file_coder_t file_coder;
    file_coder_init(&file_coder, NULL, self->method, self->key);

    code_file(&file_coder, _send_chunk, &socket);

    file_coder_uninit(&file_coder);
    socket_uninit(&socket);
}