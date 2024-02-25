#ifndef HASHTABLE_TYPE_UTIL_CHARP_JAVA_H
#define HASHTABLE_TYPE_UTIL_CHARP_JAVA_H

#include <string.h>
#include <stdbool.h>

unsigned long hash_void_charp_java(const void* key);
bool equals_void_charp_java(const void* str1, const void* str2);
char* print_void_charp_java(const void* str);
void free_void_charp_java(void* str);

#endif