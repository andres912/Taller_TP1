//
// Created by andres on 10/10/20.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "common_cipher.h"

int cesarInit(cipher_t* self);
int vigenereInit(cipher_t* self);
int rc4Init(cipher_t* self);


int cipherInit(cipher_t* self, char* method_name, char* key, int op_type) {
    if (strcmp(method_name,"cesar") == 0)
        cesarInit(self);
    else if (strcmp(method_name,"vigenere") == 0)
        vigenereInit(self);
    else if (strcmp(method_name,"rc4") == 0)
        rc4Init(self);
    return self->init_callback(self->encoder, key, op_type);
}

int cipherTranslate(cipher_t* self, unsigned char* buffer, size_t len) {
    return self->translate_callback(self->encoder, buffer, len);
}

int cipherClose(cipher_t* self) {
    return self->close_callback(self->encoder);
}

int cesarInit(cipher_t* self) {
    self-> init_callback = &cesarEncoderInit;
    self-> translate_callback = &cesarEncoderTranslate;
    self-> close_callback = &cesarEncoderClose;
    self-> encoder = malloc(sizeof(cesarEncoder_t));
    return 0;
}

int vigenereInit(cipher_t* self) {
    self-> init_callback = &vigenereEncoderInit;
    self-> translate_callback = &vigenereEncoderTranslate;
    self-> close_callback = &vigenereEncoderClose;
    self-> encoder = malloc(sizeof(vigenereEncoder_t));
    return 0;
}

int rc4Init(cipher_t* self) {
    self-> init_callback = &rc4EncoderInit;
    self-> translate_callback = &rc4EncoderTranslate;
    self-> close_callback = &rc4EncoderClose;
    self-> encoder = malloc(sizeof(rc4Encoder_t));
    return 0;
}
