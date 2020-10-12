#include "common_RC4.h"

int create(rc4_t* self, unsigned char* key) {
    self->key = key;
     _create_state_vector(self->key, self->state_vector);
    return 0;
}

void _create_state_vector(unsigned char* key, unsigned char* s) {

    for (int i = 0; i < 256; i++) {
        s[i] = i;
    }
    unsigned char j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + s[i] + key[i % strlen(key)]) % 256;
        _swap(s, i, j);
    }
}

void _swap(unsigned char* s, int pos1, int pos2) {
    unsigned char temp = s[pos1];
    s[pos1] = s[pos2];
    s[pos2] = temp;
}

void code(rc4_t* self, unsigned char *message, size_t read_bytes) {
    _create_encryption_stream(self, self->encryption_stream, read_bytes);
    for (int i = 0; i < read_bytes; i++) {
        message[i] = message[i] ^ self->encryption_stream[i];
    }
}

void _create_encryption_stream(rc4_t* self, unsigned char* K, size_t read_bytes) {

    unsigned char i = 0;
    unsigned char j = 0;

    for (int i = 0; i < read_bytes; i++) {
        i = (i + 1) % 256;
        j = (j + self->state_vector[i]) % 256;
        _swap(self->state_vector, i, j);
        K[i] = self->state_vector[ (self->state_vector[i] + self->state_vector[j]) % 256];
    }
}



