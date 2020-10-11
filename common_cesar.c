#include "common_cesar.h"

int create(cesar_t* self, int key) {
    self->key = key;
    return 0;
}

void code(cesar_t* self, unsigned char *message, size_t read_bytes){
    for (int i = 0; i < read_bytes; i++){
        message[i] = (message[i] + self->key) % 256;
    }
}

void decode(cesar_t* self, unsigned char* message, size_t read_bytes) {
    for (int i = 0; i < read_bytes; i++){
        message[i] = (message[i] - self->key) % 256;
    }
}