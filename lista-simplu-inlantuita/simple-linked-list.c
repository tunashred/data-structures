#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char* data;
    struct node* next;
};

struct simple_linked_list {
    struct node* head;
    struct node* tail;
    int size;
};

struct node* new_node(char* data);
void print_node(struct node node);
struct simple_linked_list new_simple_linked_list();
void print_list(struct simple_linked_list sll);
void push(struct simple_linked_list* sll, struct node* new_node);
char* remove_tail(struct simple_linked_list* sll);
struct node* find_first(struct simple_linked_list sll, char* data);
char* remove_first(struct simple_linked_list* sll, char* data);

int main() {
    struct simple_linked_list sll = new_simple_linked_list();
    push(&sll, new_node("azi"));
    push(&sll, new_node("nu"));
    push(&sll, new_node("mananc"));
    push(&sll, new_node("peste"));
    push(&sll, new_node("proaspat"));
    print_list(sll);
    // remove_first(&sll, "pateu");
    // remove_first(&sll, "azi");
    // remove_first(&sll, "nu");
    // remove_first(&sll, "proaspat");
    remove_tail(&sll);
    print_list(sll);
    return 0;
}

struct node* new_node(char* data) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void print_node(struct node node) {
    printf("%s ", node.data);
}

struct simple_linked_list new_simple_linked_list() {
    return (struct simple_linked_list) {};
}

void print_list(struct simple_linked_list sll) {
    for(struct node* i = sll.head; i != NULL; i = i->next) {
        print_node(*i);
    }
    printf("\n");
}

void push(struct simple_linked_list* sll, struct node* new_node) {
    if(sll->size == 0) {
        sll->head = new_node;
        sll->tail = new_node;
    }
    else {
        sll->tail->next = new_node;
        sll->tail = new_node;
    }
    sll->size++;
}

//deletes last node from list
char* remove_tail(struct simple_linked_list* sll) {
    struct node* node;
    char* data;
    switch (sll->size) {
        case 0:
            return NULL;
        case 1:
            node = sll->head;
            sll->head = NULL;
            sll->tail = NULL;
            break;
       default:
            node = sll->head;
            while(node->next->next != NULL) {
                node = node->next;
            }
            sll->tail = node;
            node = node->next;
            sll->tail->next = NULL;
            break;
    }
    data = node->data;
    free(node);
    node = NULL;
    sll->size--;
    return data;
}

struct node* find_first(struct simple_linked_list sll, char* data) {
    for(struct node* i = sll.head; i != NULL; i = i->next) {
        if( strcmp(i->data, data) == 0 ) {
            return i;
        }
    }
    return NULL;
}
 
 //deletes the first node matching the search criteria
char* remove_first(struct simple_linked_list* sll, char* data) {
    struct node *node, *aux;
    char* removed_data;
    node = sll->head;
    //case 1: the head of the list matches the search criteria
    if(strcmp(node->data, data) == 0) {
        sll->head = node->next;
        node->next = NULL;
    }
    else {
        while( (node->next != NULL) && (strcmp(node->next->data, data) != 0) ) {
            node = node->next;
        }
        //case 2: no node matches the search criteria
        if(node->next == NULL) {
            return NULL;
        }
        //case 3: the tail of the list matches the search criteria
        if(node->next->next == NULL) {
            sll->tail = node;
            node = node->next;
            sll->tail->next = NULL;
        }
        //case 4: inner node matches the search criteria
        else {
            aux = node;
            node = node->next;
            aux->next = node->next;
            node->next = NULL;
        }     
    }
    removed_data = node->data;
    free(node);
    node = NULL;
    sll->size--;
    return removed_data;
}

//     if(node == NULL) {
//         return NULL;
//     }
//     //case 3: the tail of the list matches the search criteria
//     else if(node->next == NULL) {
//         prev->next = NULL;
//         sll.tail = prev;
//     }
//     //case 4: inner node matches the search criteria
//     else {
//         prev->next = node->next;
//         node->next = NULL;
//     }
//     sll.size--;
//     return node;
// }

