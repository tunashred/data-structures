#include "hashtable_type_util_charp.h"

const unsigned short MAXLEN = 256;

static unsigned long hash_charp(const char* key) {
    unsigned long hash = 0;
    int len = (int) strnlen(key, MAXLEN);

    int i;
    for(i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

static bool equals_charp(const char* str1, const char* str2) {
    return !strncmp(str1, str2, MAXLEN);
}

static char* print_charp(const char* str) {
    return strdup(str);
}

unsigned long hash_void_charp(const void* key) {
    return hash_charp((char*) key);
}
bool equals_void_charp(const void* str1, const void* str2) {
    return equals_charp((char*) str1, (char*) str2);
}
char* print_void_charp(const void* str) {
    return print_charp((char*) str);
}

void free_void_charp(void* str) {
    return;
}