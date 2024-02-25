#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct hashtableEntry {
    void* key;
    void* value;
};

struct sll_node {
    struct hashtableEntry data;
    struct sll_node* next;
};

struct bucket {
    unsigned int size;
    struct sll_node* head;
};

typedef struct hashtable {
    unsigned int bucketCount;
    unsigned long (*__hashCode)(const void*);
    bool (*__equals)(const void*, const void*);
    char* (*__printKey)(const void*);
    char* (*__printValue)(const void*);
    void (*__freeKey)(void*);
    void (*__freeValue)(void*);
    struct bucket* buckets;
} hashtable;

hashtable* hashtable_create(
        unsigned int bucketCount,
        unsigned long (*p_func_hashCode)(const void*),
        bool (*p_func_equals)(const void*, const void*),
        char* (*p_func_printKey)(const void*),
        char* (*p_func_printValue)(const void*),
        void (*p_func_freeKey)(void*),
        void (*p_func_freeValue)(void*)
);

bool hashtable_add(hashtable* ht, const void* key, const void* value);
void* hashtable_get(hashtable* ht, const void* key);
void hashtable_print(hashtable* ht);
void* hashtable_remove(hashtable* ht, const void* key);
void hashtable_destroy(hashtable* ht);

#endif
