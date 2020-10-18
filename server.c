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

    char* method_cesar = "cesar";
    char* method_vigenere = "vigenere";
    char* method_rc4 = "rc4";

    void* coder;
    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;

    if (strcmp(self->method, method_cesar) == 0) {
        cesar_create(&cesar, self->key);
        coder = &cesar;
    } else if (strcmp(self->method, method_vigenere) == 0) {
        vigenere_create(&vigenere, self->key);
        coder = &vigenere;
    } else if (strcmp(self->method, method_rc4) == 0) {
        rc4_create(&rc4, self->key);
        coder = &rc4;
    }

    ssize_t bytes_received = 0;

    while ((bytes_received = socket_receive(&peer, buffer, BUF_SIZE)) != 0) {
        _decode_message(self, buffer, bytes_received, coder);
    }

    socket_uninit(&socket);
    socket_uninit(&peer);
}

void _decode_message(server_t* self, unsigned char* buffer, 
    ssize_t bytes_received, void* coder) {
    char* method_cesar = "cesar";
    char* method_vigenere = "vigenere";
    char* method_rc4 = "rc4";

    if (strcmp(self->method, method_cesar) == 0) {
        cesar_decode(coder, buffer, bytes_received);
    } else if (strcmp(self->method, method_vigenere) == 0) {
        vigenere_decode(coder, buffer, bytes_received);
    } else if (strcmp(self->method, method_rc4) == 0) {
        rc4_code(coder, buffer, bytes_received);
    }

    fwrite(buffer, sizeof(char), bytes_received, stdout);
}
