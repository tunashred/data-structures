#include "hashtable.h"

hashtable* hashtable_create(
        unsigned int bucketCount,
        unsigned long (*p_func_hashCode)(const void*),
        bool (*p_func_equals)(const void*, const void*),
        char* (*p_func_printKey)(const void*),
        char* (*p_func_printValue)(const void*),
        void (*p_func_freeKey)(void*),
        void (*p_func_freeValue)(void*)
) {
    hashtable* ht = (hashtable*) malloc(sizeof(hashtable));

    *ht = (hashtable) {
        .bucketCount = bucketCount,
        .__hashCode = p_func_hashCode,
        .__equals = p_func_equals,
        .__printKey = p_func_printKey,
        .__printValue = p_func_printValue,
        .__freeKey = p_func_freeKey,
        .__freeValue = p_func_freeValue,
        .buckets = (struct bucket*) calloc(bucketCount, sizeof(struct bucket))
    };
    return ht;
}

static unsigned int hashtable_index(hashtable *ht, const void* key) {
    return ht->__hashCode(key) % ht->bucketCount;
}

bool hashtable_add(hashtable *ht, const void* key, const void* value) {
    if(!ht || !key) {
        return false;
    }

    unsigned int index = hashtable_index(ht, key);
    if(ht->buckets[index].size == 0) {
        ht->buckets[index].head = (struct sll_node*) malloc(sizeof(struct sll_node));
        *(ht->buckets[index].head) = (struct sll_node) {
            .data = (struct hashtableEntry) {.key = key, .value = value},
            .next = NULL
        };
        ht->buckets[index].size = 1;
        return true;
    }

    for(struct sll_node* i = ht->buckets[index].head; i; i = i->next) {
        if(ht->__equals(key, i->data.key)) {
            i->data.value = value;
            return true;
        }
    }
    struct sll_node* node = (struct sll_node*) malloc(sizeof(struct sll_node));
    *node = (struct sll_node) {
        .data = (struct hashtableEntry) {.key = key, .value = value},
        .next = ht->buckets[index].head
    };
    ht->buckets[index].head = node;
    ht->buckets[index].size++;

    return true;
}

void* hashtable_get(hashtable *ht, const void* key) {
    if(!ht || !key) {
        return false;
    }

    unsigned int index = hashtable_index(ht, key);
    if(ht->buckets[index].size == 0) {
        return NULL;
    }

    for(struct sll_node* i = ht->buckets[index].head; i; i = i->next) {
        if(ht->__equals(key, i->data.key)) {
            return i->data.value;
        }
    }
    return NULL;
}

void hashtable_print(hashtable *ht) {
    if(!ht) {
        return;
    }

    printf("\n===============START TABLE===============\n");
    for(int i = 0; i < ht->bucketCount; i++) {
        if(ht->buckets[i].size != 0) {
            printf("[%d]:\n", i);
            for(struct sll_node* j = ht->buckets[i].head; j; j = j->next) {
                printf("%10s -> %s\n",
                        ht->__printKey(j->data.key),
                        ht->__printValue(j->data.value)
                );
            }
        }
    }
    printf("=============== END  TABLE===============\n");
}

void* hashtable_remove(hashtable *ht, const void* key) {
    if(!ht || !key) {
        return NULL;
    }

    unsigned int index = hashtable_index(ht, key);
    if(ht->buckets[index].size == 0) {
        return NULL;
    }

    struct sll_node* i;
    if(ht->__equals(key, ht->buckets[index].head->data.key)) {
        i = ht->buckets[index].head;
        ht->buckets[index].head = i->next;
    }
    else {
        struct sll_node* prev = ht->buckets[index].head;
        for(i = prev->next; i; i = i->next) {
            if(ht->__equals(key, i->data.key)) {
                prev->next = i->next;
                break;
            }
            prev = i;
        }
    }
    if(!i) {
        return NULL;
    }

    void* value = i->data.value;
    ht->buckets[index].size--;
    i->data.key = NULL;
    i->data.value = NULL;
    i->next = NULL;
    free(i);
    i = NULL;
    return value;
}

void hashtable_destroy(hashtable* ht) {
    if(!ht) {
        return;
    }

    for(int bucket = 0; bucket < ht->bucketCount; bucket++) {
        struct sll_node* i = ht->buckets[bucket].head;
        if(!i) {
            continue;
        }
        struct sll_node* next = i->next;
        while(i) {
            ht->__freeKey(i->data.key);
            ht->__freeValue(i->data.value);
            free(i);
            i = next;
            if(next) {
                next = next->next;
            }
        }
        ht->buckets[bucket].size = 0;
    }
    free(ht->buckets);
    ht->buckets = NULL;
    free(ht);
}