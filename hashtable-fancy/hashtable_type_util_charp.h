#ifndef HASHTABLE_TYPE_UTIL_CHARP_H
#define HASHTABLE_TYPE_UTIL_CHARP_H

#include "auxiliaries.h"

unsigned long hash_charp(const char* key);
unsigned long hash_void_charp(const void* key);

#endif