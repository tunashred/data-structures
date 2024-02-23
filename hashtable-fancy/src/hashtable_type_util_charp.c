#include "hashtable_type_util_charp.h"

unsigned long hash_charp(const char* key) {
    unsigned long hash = 0;
    int len = (int) strnlen(key, MAXLEN);

    for(int i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

unsigned long hash_void_charp(const void* key) {
    return hash_charp((char*) key);
}