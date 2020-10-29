#include "common_encryptor.h"

cesar_t* get_cesar(encryptor_t* self) {
    return &self->cesar;
}

vigenere_t* get_vigenere(encryptor_t* self) {
    return &self->vigenere;
}

rc4_t* get_rc4(encryptor_t* self) {
    return &self->rc4;
}