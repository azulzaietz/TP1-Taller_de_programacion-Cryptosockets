#include "client.h"

void init_client(client_t* self, int argc, char* const* argv) {
    _read_command_line(self, argc, argv);
}

void _read_command_line(client_t* self, int argc, char* const* argv) {	
    self->server_host = argv[1];
    self->server_port = argv[2];

    read_long_options(&self->method, &self->key, argc, argv);
}

void send_coded_message_to_server(client_t* self) {
    socket_t socket;
    socket_connect(&socket, self->server_host, self->server_port);

    file_coder_t file_coder;
    file_coder_init(&file_coder, NULL);

    char* method_cesar = "cesar";
    char* method_vigenere = "vigenere";
    char* method_rc4 = "rc4";

    void* coder = NULL;
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

    code_file(&file_coder, &socket, coder, self->method);

    file_coder_uninit(&file_coder);
    socket_uninit(&socket);
}
