#include "common_socket.h"

void socket_init(socket_t* self){}
void socket_uninit(socket_t* self){}

void socket_bind_and_listen(socket_t* self, const char* host, const char* service){}
void socket_accept(socket_t* listener, socket_t* peer){}

void socket_connect(socket_t* self, const char* host, const char* service){}

ssize_t socket_send(socket_t* self, const char* buffer, size_t length){}
ssize_t socket_receive(socket_t* self, const char* buffer, size_t length){}

static void _send_chunk(const char *chunk, size_t chunk_size, void *callback_ctx) {
	socket_t *socket = callback_ctx;
	socket_send(socket, chunk, chunk_size);
}