/*#include "common_coder_selector.h"

void coder_selector_init(coder_selector_t* self, const char* method, const char* key) {
    self->key = key;
    _select_coder_method(self, method);
}

void _select_coder_method(coder_selector_t* self, const char* method) {
    
    char* method_cesar = "cesar";
    char* method_vigenere = "vigenere";
    char* method_rc4 = "rc4";

    cesar_t cesar;
    vigenere_t vigenere;
    rc4_t rc4;

    if (strcmp(method, method_cesar) == 0) {
        
        self->coder = &cesar;
        cesar_create(self->coder, self->key);
        self->coder_t = &cesar_code;

    } if (strcmp(method, method_vigenere) == 0) {

        self->coder = &vigenere;
        vigenere_create(self->coder, self->key);
        self->coder_t = &vigenere_code;

    } if (strcmp(method, method_rc4) == 0) {
 
        self->coder = &rc4;
        rc4_create(self->coder, self->key);
        self->coder_t = &rc4_code;

    }

}
*/