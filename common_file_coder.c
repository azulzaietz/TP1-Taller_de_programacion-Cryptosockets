#include "common_file_coder.h"

int file_coder_init(file_coder_t* self, const char* file_name) {
    if (file_name == NULL) {
        self->fp = stdin;
    } else {
        self->fp = fopen(file_name, "rb");
    }
    return 0;
}

int file_coder_uninit(file_coder_t* self) {
    if (self->fp != stdin) {
        if (fclose(self->fp) == EOF) {
//            printf(stderr, "file_reader_uninit-->close %s\n", 
//              strerror(errno));
            return -1;
        }
    }
    return 0;
}

size_t code_file(file_coder_t* self, unsigned char* buffer, 
    coder_selector_t* coder_selector, const char* method) {
    size_t read_bytes = 0;
    
    while (!feof(self->fp)) {
        read_bytes = fread(buffer, sizeof(char), BUF_SIZE, self->fp);
        code(coder_selector, buffer, read_bytes);
        socket_send(socket, buffer, read_bytes);
    }
    return read_bytes;
}
