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

/**
 * @brief Hashtable creation
 * 
 * @param bucketCount       number of buckets
 * @param p_func_hashCode   function pointer to hash function
 * @param p_func_equals     function pointer to comparison function
 * @param p_func_printKey   function pointer to printKey function
 * @param p_func_printValue function pointer to printValue function
 * @param p_func_freeKey    function pointer to free key function
 * @param p_func_freeValue  function pointer to free value function
 * @return hashtable* instance ready to use
 */
hashtable* hashtable_create(
        unsigned int bucketCount,
        unsigned long (*p_func_hashCode)(const void*),
        bool (*p_func_equals)(const void*, const void*),
        char* (*p_func_printKey)(const void*),
        char* (*p_func_printValue)(const void*),
        void (*p_func_freeKey)(void*),
        void (*p_func_freeValue)(void*)
);

/**
 * @brief Hashtable add entry
 * 
 * @param ht      instance of hashtable
 * @param key     key to be hashed
 * @param value   storing value
 * @returns
 *      - true:  if the entry was added successfully
 *      - false: if the hashtable or key is NULL
 */
bool hashtable_add(hashtable* ht, const void* key, const void* value);

/**
 * @brief Get value by key from hashtable
 * 
 * @param ht  instance of hashtable
 * @param key search key
 * @returns
 *      - void* value: if entry found
 *      - null: 
 *           - if hashtable or key is NULL
 *           - if entry not found
 */
void* hashtable_get(hashtable* ht, const void* key);

void hashtable_print(hashtable* ht);

/**
 * @brief Removes entry matching key
 * 
 * @param ht  instance of hashtable
 * @param key search key
 * @returns
 *      - void* value: if entry was removed
 *      - null: 
 *           - if hashtable or key is NULL
 *           - if hashtable is empty
 *           - if entry not found
 */
void* hashtable_remove(hashtable* ht, const void* key);

/**
 * @brief    Frees instance of hashtable and all its entries
 * 
 * @param ht instance of hashtable
 */
void hashtable_destroy(hashtable* ht);

#endif
