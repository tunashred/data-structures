#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "hashtable_type_util_charp.h"
#include "hashtable_type_util_charp_java.h"
#include "auxiliaries.h"

int main() {
    hashtable_create(69, &hash_void_charp, &printKey_void_charp, &printValue_void_charp);
    

    return 0;
}
