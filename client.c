#include "client.h"

void init_client(client_t* self, const char* server_host, 
    const char* server_port, int argc, char* const* argv) {
    self->server_host = server_host;
    self->server_port = server_port;
    _read_command_line(self, argc, argv);
}

void _read_command_line(client_t* self, int argc, char* const* argv){	
    const char* str_key = "key";
    const char* str_method = "method";
	const char* method_cesar = "cesar";
    const char* method_vigenere = "vigenere";
    const char* method_rc4 = "rc4";

    const char* option;
    int option_index = 0;
    int c = 0;

    static struct option long_options[] = {
        {"method", required_argument, 0,  0 },
        {"key", required_argument, 0,  0 },
    };

	while (c != -1){
		c = getopt_long(argc, argv, "-:abc:d::", long_options, &option_index);

       	if (c == 0) {
        	option = long_options[option_index].name;

			if (strcmp(option, str_method) == 0) {
				if (strcmp(optarg, method_cesar) == 0){
		          	self->method = "cesar";
				} else if (strcmp(optarg, method_vigenere) == 0){
					self->method = "vigenere";
				} else if (strcmp(optarg, method_rc4) == 0){
					self->method = "rc4";
				} else{
					printf("No se pasaron metodos\n");
				}
			} else if (strcmp(long_options[option_index].name, str_key) == 0){
				self->key = optarg;
			}
        }
	}
}

/************************************ TODO QUE FUNCIONE ESTA **********************************
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
**********************************************************************************************/


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
