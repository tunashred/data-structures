#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "hashtable_type_util_charp.h"
#include "hashtable_type_util_charp_java.h"

int main() {
    hashtable* ht = hashtable_create(
        10,
        &hash_void_charp_java,
        &equals_void_charp_java,
        &print_void_charp_java,
        &print_void_charp_java,
        &free_void_charp_java,
        &free_void_charp_java
        );
    
    hashtable_add(ht, "ana", "are mere dulci");
    hashtable_add(ht, "diana", "are mere acre");
    hashtable_add(ht, "alin", "are peste proaspat");
    hashtable_add(ht, "enash", "are peste stricat");
    hashtable_add(ht, "david", "s-a spart cu mahoarca iara");
    hashtable_add(ht, "enash", "are peste crud");

    hashtable_print(ht);

    hashtable_remove(ht, "alin");
    hashtable_remove(ht, "enash");

    hashtable_print(ht);
    hashtable_destroy(ht);

    return 0;
}
