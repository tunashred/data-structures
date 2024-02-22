#include "hashtable.h"

// returns hashtable
void hashtable_create(
        unsigned int bucketCount,
        unsigned long (*p_func_hashCode)(void*),
        char* (*p_func_printKey)(void*),
        char* (*p_func_printValue)(void*)
) {
    char* key = "caca";
    char* value = "pipi";

    printf("%lu %s %s\n",
            (*p_func_hashCode)(key),
            (*p_func_printKey)(key),
            (*p_func_printValue)(value)
    );
    
    return;
}