#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXLEN 256

struct user {
    char *name;
    char *nickname;
    struct user *next;
};

typedef struct hashtable {
    int size;
    struct user **bucket;
} hashtable;

int hash(char *key) {
    long long hash = 0;
    int len = (int) strnlen(key, MAXLEN);

    for(int i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return (int) hash;
}

unsigned int java_hashCode(const char *key) {
    unsigned int hash = 0;
    for(int i = 0; i < strnlen(key, MAXLEN); i++) {
        hash = 31 * hash + key[i];
    }
    return hash;
}

hashtable *hashtable_create(int initialBucketCount) {
    hashtable *ht = malloc(sizeof *ht);
    ht->size = initialBucketCount;
    ht->bucket = calloc(sizeof(struct user*), ht->size);

    return ht;
}

void hashtable_print(hashtable *ht) {
    if(!ht) {
        printf("Invalid hashtable.\n");
        return;
    }

    printf("\nStart table:\n");
    for(int i = 0; i < ht->size; i++) {
        if(ht->bucket[i]) {
            printf("\t%d\t\n", i);
            struct user *users_bucket = ht->bucket[i];

            while(users_bucket) {
                printf("\t%s a.k.a. \"%s\"", users_bucket->name, users_bucket->nickname);
                if(users_bucket->next) {
                    printf("  ----");
                }
                users_bucket = users_bucket->next;
            }
            printf("\n");
        }
    }
    printf("End table.\n");
}

int hashtable_index(hashtable *ht, char *key) {
    return java_hashCode(key) % ht->size;
}

char *hashtable_lookup(hashtable *ht, char *key) {
    if(!key || !ht) {
        return NULL;
    }

    int index = hashtable_index(ht, key);
    struct user *users_bucket = ht->bucket[index];

    while(users_bucket) {
        if(!strncmp(key, users_bucket->name, MAXLEN)) {
            return users_bucket->name;
        }
        users_bucket = users_bucket->next;
    }

    return NULL;
}

bool hashtable_insert(hashtable *ht, char *name, char *nickname) {
    if(!name || !nickname || !ht) {
        printf("Insertion failed. Invalid input.\n");
        return false;
    }

    int name_len     = (int) strnlen(name, MAXLEN),
            nickname_len = (int) strnlen(nickname, MAXLEN);

    if(name_len == MAXLEN || nickname_len == MAXLEN) {
        printf("Name or nickname exceeding length limit.\n");
        return false;
    }

    if(hashtable_lookup(ht, name)) {
        int index = hashtable_index(ht, name);
        struct user *i = ht->bucket[index];

        while(i) {
            if(!strncmp(name, i->name, MAXLEN)) {
                char *temp = realloc(i->nickname, sizeof(char) * (nickname_len + 1));
                if(!temp) {
                    printf("Resizing nickname string failed.\n");
                    return false;
                }
                i->nickname = temp;
                strncpy(i->nickname, nickname, nickname_len);
                i->nickname[nickname_len] = '\0';

                return true;
            }
            i = i->next;
        }
    }

    struct user *new_user = (struct user*) malloc(sizeof *new_user);

    new_user->name = (char*) malloc(sizeof(char) * (name_len + 1));
    strncpy(new_user->name, name, name_len);
    new_user->name[name_len] = '\0';

    new_user->nickname = (char*) malloc(sizeof(char) * (nickname_len + 1));
    strncpy(new_user->nickname, nickname, nickname_len);
    new_user->nickname[nickname_len] = '\0';
    new_user->next = NULL;

    int index = hashtable_index(ht, name);
    struct user *users_bucket = ht->bucket[index];

    if(!users_bucket) {
        ht->bucket[index] = new_user;
    }
    else {
        while(users_bucket->next) {
            users_bucket = users_bucket->next;
        }
        users_bucket->next = new_user;
    }

    return true;
}

void free_user(struct user *user) {
    free(user->name);
    free(user->nickname);
    user->name = NULL;
    user->nickname = NULL;
    user->next = NULL;
    free(user);
    user = NULL;
}

char *hashtable_remove(hashtable *ht, char *key) {
    if(!ht) {
        printf("Invalid hash table.\n");
        return NULL;
    }

    if(!hashtable_lookup(ht, key)) {
        printf("User does not exist.\n");
        return NULL;
    }

    int index = hashtable_index(ht, key);
    struct user *curr = ht->bucket[index];
    struct user *prev = NULL;

    while(curr) {
        if (!strncmp(key, curr->name, MAXLEN)) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if(!curr) {
        printf("User not found.\n");
        return NULL;
    }

    if(!prev) {
        ht->bucket[index] = curr->next;
    }
    else {
        prev->next = curr->next;
    }
    free_user(curr);

    return key;
}

void hashtable_destroy(hashtable *ht) {
    if(!ht) {
        printf("Invalid hash table.\n");
        return;
    }

    for(int i = 0; i < ht->size; i++) {
        struct user *curr = ht->bucket[i];
        while(curr) {
            struct user *prev = curr;
            curr = curr->next;
            free_user(prev);
        }
    }

    free(ht->bucket);
    ht->bucket = NULL;
    ht->size = 0;
    free(ht);
    ht = NULL;
}

void dispersion_test(char *filename, int ht_size) {
    FILE *myFile;

    if( (myFile = fopen(filename, "rt")) == 0 ) {
        printf("Error opening file.\n");
        return;
    }

    hashtable *ht = hashtable_create(ht_size);
    char word[MAXLEN];
    while(!feof(myFile)) {
        fscanf(myFile, "%s", word);
        hashtable_insert(ht, word, word);
    }

    int bucket_weights[100] = { [0 ... 99] = 0 };
    int min = (1 << 30), max = 0, total_users = 0;

    for(int i = 0; i < ht->size; i++) {
        int users_count = 0;
        for(struct user *j = ht->bucket[i]; j; j = j->next) {
            users_count++;
        }

        if(min > users_count) {
            min = users_count;
        }
        if(max < users_count) {
            max = users_count;
        }
        total_users += users_count;

        int bucket_size = (int) fmin(100, users_count);
        bucket_weights[ bucket_size ] ++;
        printf("Bucket %d: %d users\n", i, users_count);
    }

    hashtable_destroy(ht);

    printf("\nLeast users in a bucket: %d\n", min);
    printf("Most users in a bucket: %d\n", max);
    printf("Range of users: %d\n", max - min);
    printf("Total users: %d\n", total_users);
    printf("Number of buckets with X users: \n");
    for(int i = 0; i < 10; i++) {
        printf("%-7d", bucket_weights[i]);
    }
    printf("\n");
    for(int i = 0; i < 10; i++) {
        printf("%-7d", i);
    }
    printf("\n----------------------------------\n");

    fclose(myFile);
}

int main() {
    hashtable *ht = hashtable_create(100);
    hashtable_insert(ht, "Andrei", "Gulie");
    hashtable_insert(ht, "Mihai", "Bibanu");
    hashtable_insert(ht, "Adrian", "Capy");
    hashtable_insert(ht, "Goran", "Matahala");
    hashtable_insert(ht, "Parizer", "Parizer");
    hashtable_insert(ht, "Parizer", "Parizer");
    hashtable_insert(ht, "Andreiul", "Guliu");

    char *removed_user = hashtable_remove(ht, "Mihai");
    printf("%s\n", removed_user);

    hashtable_print(ht);
    hashtable_destroy(ht);

    int eng_words = 466550;
    int ro_words = 178562;
    dispersion_test("./input_eng.txt", eng_words);
    dispersion_test("./input_ro.txt", ro_words);

    return 0;
}
