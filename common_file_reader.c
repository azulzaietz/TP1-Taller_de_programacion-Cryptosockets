#include "common_file_reader.h"
#include <errno.h>
#include <string.h>

int file_open(file_reader_t* self, const char* file_name) {

    if (file_name == NULL) {
        self->fp = stdin;
        return 0;
    } else {
        self->fp = fopen(file_name, "rb");
    }

    if(!self->fp) {
//        printf(stderr, "file_reader_init-->open %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

int file_close(file_reader_t* self) {
    if (self->fp != stdin) {
        if (fclose(self->fp) == EOF) {
//            printf(stderr, "file_reader_uninit-->close %s\n", strerror(errno));
            return -1;
        }
    }
    return 0;
}

int read_file(file_reader_t* self, file_reader_callback_t callback, void* callback_ctx) {

    char buffer[BUF_SIZE];

    while(!feof(self->fp)){
        size_t read_bytes = fread(buffer, sizeof(char), BUF_SIZE, self->fp);
        callback(buffer, read_bytes, callback_ctx);
    }
    return 0;
}