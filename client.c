#include "client.h"
#include "common_file_coder.h"
#include "common_coder_selector.h"
#include "common_socket.h"
#include "common_long_option_reader.h"

//Lee los parametros de la linea de comandos
static void _read_command_line(client_t* self, int argc, char* const* argv) {	
    self->server_host = argv[1];
    self->server_port = argv[2];

    read_long_options(&self->method, &self->key, argc, argv);
}

void init_client(client_t* self, int argc, char* const* argv) {
    _read_command_line(self, argc, argv);
}

void send_coded_message_to_server(client_t* self) {
    socket_t socket;
    socket_connect(&socket, self->server_host, self->server_port);

    encryptor_t encryptor;
    coder_selector_t coder_selector;
    coder_selector_init(&coder_selector, self->method, self->key, 
        &encryptor);

    file_coder_t file_coder;
    file_coder_init(&file_coder, NULL);

    code_file(&file_coder, &socket, &coder_selector, self->method);

    file_coder_uninit(&file_coder);
    socket_uninit(&socket);
}
