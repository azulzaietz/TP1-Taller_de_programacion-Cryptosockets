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

    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;
    coder_selector_t coder_selector;
    coder_selector_init(&coder_selector, self->method, self->key, 
        &cesar, &vigenere, &rc4);

    file_coder_t file_coder;
    file_coder_init(&file_coder, NULL);

    unsigned char buffer[BUF_SIZE];
    size_t read_bytes = code_file(&file_coder, buffer, 
    &coder_selector, self->method);

    socket_send(&socket, buffer, read_bytes);

    file_coder_uninit(&file_coder);
    socket_uninit(&socket);
}
