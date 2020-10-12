#include "common_vigenere.h"

int create(vigenere_t* self, unsigned char* key) {
    self->key = key;
    return 0;
}

void code(vigenere_t* self, unsigned char *message, size_t read_bytes) {
    for (int i = 0; i < read_bytes; i++){
        message[i] = (message[i] + self->key[i % strlen(self->key)]) % 256;
    }
}

void decode(vigenere_t* self, unsigned char* message, size_t read_bytes) {
    for (int i = 0; i < read_bytes; i++){
        message[i] = (message[i] - self->key[(i % strlen(self->key))]) % 256;
    }
}