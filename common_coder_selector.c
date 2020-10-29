#include "common_coder_selector.h"

//Crea el cifrador que corresponde al metodo pasado por parametro
//en la inicializacion del selector.
static void _select_coder_method(coder_selector_t* self) {
    char* method_cesar = "cesar";
    char* method_vigenere = "vigenere";
    char* method_rc4 = "rc4";

    if (strcmp(self->method, method_cesar) == 0) {
        self->coder = self->cesar;
        cesar_create(self->coder, self->key);
    } else if (strcmp(self->method, method_vigenere) == 0) {
        self->coder = self->vigenere;
        vigenere_create(self->coder, self->key);
    } else if (strcmp(self->method, method_rc4) == 0) {
        self->coder = self->rc4;
        rc4_create(self->coder, self->key);
    }
}

void coder_selector_init(coder_selector_t* self, const char* method,
const char* key, encryptor_t* encryptor) {
    self->key = key;
    self->method = method;
    self->cesar = get_cesar(encryptor);
    self->vigenere = get_vigenere(encryptor);
    self->rc4 = get_rc4(encryptor);
    _select_coder_method(self);
}

void code(coder_selector_t* self, unsigned char* buffer,
size_t read_bytes) {
    char* method_cesar = "cesar";
    char* method_vigenere = "vigenere";
    char* method_rc4 = "rc4";

    if (strcmp(self->method, method_cesar) == 0) {
        cesar_code(self->coder, buffer, read_bytes);
    } else if (strcmp(self->method, method_vigenere) == 0) {
        vigenere_code(self->coder, buffer, read_bytes);
    } else if (strcmp(self->method, method_rc4) == 0) {
        rc4_code(self->coder, buffer, read_bytes);
    }
}

void decode(coder_selector_t* self, unsigned char* buffer,
size_t read_bytes) {
    char* method_cesar = "cesar";
    char* method_vigenere = "vigenere";
    char* method_rc4 = "rc4";

    if (strcmp(self->method, method_cesar) == 0) {
        cesar_decode(self->coder, buffer, read_bytes);
    } else if (strcmp(self->method, method_vigenere) == 0) {
        vigenere_decode(self->coder, buffer, read_bytes);
    } else if (strcmp(self->method, method_rc4) == 0) {
        rc4_code(self->coder, buffer, read_bytes);
    }
}
