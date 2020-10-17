#include "client.h"

void init_client(client_t* self, const char* server_host, const char* server_port, const char* method, const char* key) {
    self->server_host = server_host;
    self->server_port = server_port;
    self->method = method;
    self->key = key;
}

void send_coded_message_to_server(client_t* self) {
    
    socket_t socket;
    socket_connect(&socket, self->server_host, self->server_port);

    coder_selector_t coder_selector;
    coder_selector_init(&coder_selector, self->method, self->key);

    file_coder_t file_coder;
    file_coder_init(&file_coder, NULL, &coder_selector);

    code_file(&file_coder, &socket);

    file_coder_uninit(&file_coder);
    socket_uninit(&socket);
}