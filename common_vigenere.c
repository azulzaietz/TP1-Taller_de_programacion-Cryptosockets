#include "common_vigenere.h"

int vigenere_create(vigenere_t* self, const char* key) {
    self->key = key;
    return 0;
}

void vigenere_code(vigenere_t* self, unsigned char *message, size_t read_bytes) {
    for (int i = 0; i < read_bytes; i++){
        message[i] = (message[i] + (unsigned char) self->key[i % strlen(self->key)]) % 256;
    }
}

void vigenere_decode(vigenere_t* self, unsigned char* message, size_t read_bytes) {
    for (int i = 0; i < read_bytes; i++){
        message[i] = (message[i] - (unsigned char) self->key[i % strlen(self->key)]) % 256;
    }
}