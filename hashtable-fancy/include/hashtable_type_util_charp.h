#ifndef HASHTABLE_TYPE_UTIL_CHARP_H
#define HASHTABLE_TYPE_UTIL_CHARP_H

#include <string.h>
#include <stdbool.h>

unsigned long hash_void_charp(const void* key);
bool equals_void_charp(const void* str1, const void* str2);
char* print_void_charp(const void* str);
void free_void_charp(void* str);

#endif