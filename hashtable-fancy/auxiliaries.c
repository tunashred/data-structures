#include "auxiliaries.h"

const unsigned short MAXLEN = 256;

char* printKey_void_charp(void* key) {
    return printKey_charp((char*) key);
}

char* printValue_void_charp(void* value) {
    return printValue_charp((char*) value);
}

char* printKey_charp(char* key) {
    return key;
}

char* printValue_charp(char* value) {
    return value;
}