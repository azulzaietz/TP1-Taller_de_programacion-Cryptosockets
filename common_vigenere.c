#include "common_vigenere.h"

int vigenere_create(vigenere_t* self, const char* key) {
    self->len_key = strlen(key);
    self->key = (unsigned char*) key;
    self->pos_key = 0;
    return 0;
}

void vigenere_code(vigenere_t* self, unsigned char *message, size_t read_bytes) {
    for (int i = 0; i < read_bytes; i++){
        message[i] = (message[i] + self->key[self->pos_key % self->len_key]) % 256;
        self->pos_key++;
    }
}

void vigenere_decode(vigenere_t* self, unsigned char* message, size_t read_bytes) {
    for (int i = 0; i < read_bytes; i++){
        message[i] = (message[i] - self->key[self->pos_key % self->len_key]) % 256;
        self->pos_key++;
    }
}