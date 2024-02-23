#ifndef AUXILIARIES_H
#define AUXILIARIES_H

#include <stdio.h>
#include <string.h>

extern const unsigned short MAXLEN;

char* printKey_charp(char* key);
char* printKey_void_charp(void* key);

char* printValue_charp(char* value);
char* printValue_void_charp(void* value);

#endif