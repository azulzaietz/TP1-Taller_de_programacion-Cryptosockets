#include "common_file_coder.h"

/************************* TODO QUE FUNCIONE ESTA ********************************************/
/*********************************************************************************************
int file_coder_init(file_coder_t* self, const char* file_name, coder_selector_t* coder_selector) {

    if (file_name == NULL) self->fp = stdin;
    else self->fp = fopen(file_name, "rb");

    if(!self->fp) {
//        printf(stderr, "file_reader_init-->open %s\n", strerror(errno));
        return -1;
    }

    self->coder_selector = coder_selector;

    return 0;
}

int file_coder_uninit(file_coder_t* self) {
    if (self->fp != stdin) {
        if (fclose(self->fp) == EOF) {
//            printf(stderr, "file_reader_uninit-->close %s\n", strerror(errno));
            return -1;
        }
    }
    return 0;
}

int code_file(file_coder_t* self, socket_t* socket) {

    unsigned char buffer[BUF_SIZE];

    while(!feof(self->fp)){

        size_t read_bytes = fread(buffer, sizeof(char), BUF_SIZE, self->fp);
        self->coder_selector->coder_t(self->coder_selector->coder, buffer, read_bytes);
        socket_send(socket, buffer, read_bytes);
    }
    return 0;
}
/************************************************************************************************/
int file_coder_init(file_coder_t* self, const char* file_name) {

    if (file_name == NULL) self->fp = stdin;
    else self->fp = fopen(file_name, "rb");

    return 0;
}

int file_coder_uninit(file_coder_t* self) {
    if (self->fp != stdin) {
        if (fclose(self->fp) == EOF) {
//            printf(stderr, "file_reader_uninit-->close %s\n", strerror(errno));
            return -1;
        }
    }
    return 0;
}

int code_file(file_coder_t* self, socket_t* socket, void* coder, const char* method) {

    unsigned char buffer[BUF_SIZE];

    char* method_cesar = "cesar";
    char* method_vigenere = "vigenere";
    char* method_rc4 = "rc4";

    while(!feof(self->fp)){

        size_t read_bytes = fread(buffer, sizeof(char), BUF_SIZE, self->fp);

        if (strcmp(method, method_cesar) == 0) {
            
	        cesar_code(coder, buffer, read_bytes);

	    } if (strcmp(method, method_vigenere) == 0) {

	        vigenere_code(coder, buffer, read_bytes);

	    } if (strcmp(method, method_rc4) == 0) {
	 
	        rc4_code(coder, buffer, read_bytes);

	    }
        socket_send(socket, buffer, read_bytes);
    }
    return 0;
}