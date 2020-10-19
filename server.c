#include "server.h"

void server_init(server_t* self, int argc, char* const* argv) {
    _read_command_line(self, argc, argv);
}

void _read_command_line(server_t* self, int argc, char* const* argv) {	
    self->server_port = argv[1];
    read_long_options(&self->method, &self->key, argc, argv);
}

void receive_coded_message_from_client(server_t* self) {
    socket_t socket;
	socket_t peer;
	unsigned char buffer[BUF_SIZE];

    socket_bind_and_listen(&socket, NULL, self->server_port);

    socket_accept(&socket, &peer);

    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;
    coder_selector_t coder_selector;
    coder_selector_init(&coder_selector, self->method, self->key, 
        &cesar, &vigenere, &rc4);

    ssize_t bytes_received = 0;

    while ((bytes_received = socket_receive(&peer, buffer, BUF_SIZE)) != 0) {
        decode(&coder_selector, buffer, bytes_received);
        fwrite(buffer, sizeof(char), bytes_received, stdout);
    }

    socket_uninit(&socket);
    socket_uninit(&peer);
}

