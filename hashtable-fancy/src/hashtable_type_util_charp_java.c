#include "hashtable_type_util_charp_java.h"

const unsigned short MAXLEN = 256;

static unsigned long hash_charp_java(const char *key) {
    unsigned long hash = 0;
    int i;
    for(i = 0; i < strnlen(key, MAXLEN); i++) {
        hash = 31 * hash + key[i];
    }
    return hash;
}

static bool equals_charp_java(const char* str1, const char* str2) {
    return !strncmp(str1, str2, MAXLEN);
}

static char* print_charp_java(const char* str) {
    return strdup(str);
}

unsigned long hash_void_charp_java(const void* key) {
    return hash_charp_java((char*) key);
}
bool equals_void_charp_java(const void* str1, const void* str2) {
    return equals_charp_java((char*) str1, (char*) str2);
}
char* print_void_charp_java(const void* str) {
    return print_charp_java((char*) str);
}

void free_void_charp_java(void* str) {
    return;
}