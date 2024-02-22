#include "hashtable_type_util_charp_java.h"
#include "auxiliaries.h"

unsigned long hash_charp_java(const char *key) {
    unsigned long hash = 0;
    for(int i = 0; i < strnlen(key, MAXLEN); i++) {
        hash = 31 * hash + key[i];
    }
    return hash;
}

unsigned long hash_void_charp_java(const void* key) {
    return hash_charp_java((char*) key);
}