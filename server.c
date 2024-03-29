#include "server.h"
#include "common_socket.h"
#include "common_coder_selector.h"
#include "common_long_option_reader.h"

//Lee los parametros pasados por linea de comandos para
//inicializar el servidor.
static void _read_command_line(server_t* self, int argc, char* const* argv) {	
    self->server_port = argv[1];
    read_long_options(&self->method, &self->key, argc, argv);
}

void server_init(server_t* self, int argc, char* const* argv) {
    _read_command_line(self, argc, argv);
}

void receive_coded_message_from_client(server_t* self) {
    socket_t socket;
	socket_t peer;
	unsigned char buffer[BUF_SIZE];

    socket_bind_and_listen(&socket, NULL, self->server_port);

    socket_accept(&socket, &peer);

    encryptor_t encryptor;
    coder_selector_t coder_selector;
    coder_selector_init(&coder_selector, self->method, self->key, 
        &encryptor);

    ssize_t bytes_received = 0;

    while ((bytes_received = socket_receive(&peer, buffer, BUF_SIZE)) != 0) {
        decode(&coder_selector, buffer, bytes_received);
        fwrite(buffer, sizeof(char), bytes_received, stdout);
    }

    socket_uninit(&socket);
    socket_uninit(&peer);
}

