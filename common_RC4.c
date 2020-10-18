#include "common_RC4.h"

int rc4_create(rc4_t* self, const char* key) {
    self->i = 0;
    self->j = 0;
     _create_state_vector(key, self->state_vector);
    return 0;
}

void _create_state_vector(const char* key, unsigned char* s) {
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

void rc4_code(rc4_t* self, unsigned char *message, size_t read_bytes) {
    for (int i = 0; i < read_bytes; i++) {
        self->i = (self->i + 1) % 256;
        self->j = (self->j + self->state_vector[self->i]) % 256;
        _swap(self->state_vector, self->i, self->j);
        unsigned char pos = self->state_vector[self->i] + self->state_vector[self->j];
        message[i] = message[i] ^ self->state_vector[ pos % 256];
    }
}
