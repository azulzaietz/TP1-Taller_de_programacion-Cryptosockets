#include "common_vigenere.h"

int vigenere_create(vigenere_t* self, const char* key) {
    self->len_key = strlen(key);
    self->key = (unsigned char*) key;
    return 0;
}

void vigenere_code(vigenere_t* self, unsigned char *message, size_t read_bytes) {
    for (int i = 0; i < read_bytes; i++){
        message[i] = (message[i] + self->key[i % self->len_key]) % 256;
    }
}

void vigenere_decode(vigenere_t* self, unsigned char* message, size_t read_bytes) {
    for (int i = 0; i < read_bytes; i++){
        message[i] = (message[i] - self->key[i % self->len_key]) % 256;
    }
}