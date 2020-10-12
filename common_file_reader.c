#include "common_file_reader.h"
#include <errno.h>
#include <string.h>
/*#include <iostream>
#include <exception>*/

int file_reader_init(file_reader_t* self, const char* file_name) {
    self->fp = file_name != NULL ? fopen(file_name, "rb") : stdin;
    if(!self->fp) {
        printf('File open failed %s\n', strerror(errno));
        return -1;
    }
    /*try {
        self->fp = file_name != NULL ? fopen(file_name, "rb") : stdin;
        if(!self->fp) throw new Exception(errno, 'File open failed.');
    } catch (Exception $e) {
        echo "Error (File: ".$e->getFile().", line ".$e->getLine()."): ".$e->getMessage();
        printf("Something went wrong with fopen() %s\n", strerror(errno));
    } */
    return 0;
}

int file_reader_uninit(file_reader_t* self) {
    if (self->fp != stdin) {
        if (fclose(self->fp) == EOF) return -1;
    }
    return 0;
    /*try {
        if(self->fp != stdin) int fc = fclose(self->fp);
        if(fc == EOF) throw new Exception(errno, 'File close failed.');
    } catch (Exception $e) {
        echo "Error (File: ".$e->getFile().", line ".$e->getLine()."): ".$e->getMessage();
        printf("Something went wrong with fclose() %s\n", strerror(errno));
    }*/
}

int file_reader_iterate(file_reader_t* self, file_reader_callback_t callback, void* callback_ctx) {
    char buffer[BUF_SIZE];
    while(!feof(self->fp)){
        size_t read_bytes = fread(buffer, sizeof(char), BUF_SIZE, self->fp);
        callback(buffer, read_bytes, callback_ctx);
    }
    return 0;
}
