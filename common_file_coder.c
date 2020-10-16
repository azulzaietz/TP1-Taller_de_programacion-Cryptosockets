#include "common_file_coder.h"

int file_coder_init(file_coder_t* self, const char* file_name, const char* method, const char* key) {

    if (file_name == NULL) self->fp = stdin;
    else self->fp = fopen(file_name, "rb");

/*
    if(!self->fp) {
//        printf(stderr, "file_reader_init-->open %s\n", strerror(errno));
        return -1;
    }*/

    _init_coder_method(self, method, key);

    return 0;
}

void _init_coder_method(file_coder_t* self, const char* method, const char* key) {
    
    char* method_cesar = "cesar";
    char* method_vigenere = "vigenere";
    char* method_rc4 = "rc4";

    if (strcmp(method, method_cesar) == 0) {
        
        cesar_t* cesar;
        self->coder = cesar;
        cesar_create(self->coder, key);
        coder_t = &cesar_code;

    } if (strcmp(method, method_vigenere) == 0) {

        vigenere_t* vigenere;
        self->coder = vigenere;
        vigenere_create(self->coder, key);
        coder_t = &vigenere_code;

    } if (strcmp(method, method_rc4) == 0) {
 
        rc4_t* rc4;
        self->coder = rc4;
        rc4_create(self->coder, key);
        coder_t = &rc4_code;

    }

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

int code_file(file_coder_t* self, file_coder_callback_t callback, void* callback_ctx) {

    char buffer[BUF_SIZE];

    while(!feof(self->fp)){
        size_t read_bytes = fread(buffer, sizeof(char), BUF_SIZE, self->fp);
        //coder_t(self->coder, buffer, read_bytes);
        callback(buffer, read_bytes, callback_ctx);
    }
    return 0;
}