#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char* data;
    struct node* next;
    struct node* prev;
};

struct double_linked_list {
    struct node* head;
    struct node* tail;
    int size;
};

struct node* new_node(char* data);
struct double_linked_list new_dll();
void print_node(struct node* node);
void print_dll(struct double_linked_list* dll);
void push_tail(struct double_linked_list* dll, char* data);
char* remove_tail(struct double_linked_list* dll);
struct node* find_first(struct double_linked_list dll, char* data);
void free_node(struct node** node);
void free_all_nodes(struct double_linked_list* dll);
char* remove_first(struct double_linked_list* dll, char* data);
void push_head(struct double_linked_list* dll, char* data);
char* remove_head(struct double_linked_list* dll);
int contains(struct double_linked_list dll, char* data);
void add_after(struct double_linked_list* dll, struct node* node, char* data);

int main() {
    struct double_linked_list dll = new_dll();
    push_tail(&dll, "Azi");
    push_tail(&dll, "nu");
    push_tail(&dll, "mananc");
    push_tail(&dll, "peste");
    push_tail(&dll, "proaspat");
    print_dll(&dll);
    print_dll(&dll);
    // free_all_nodes(&dll);
    // print_dll(&dll);
    // push_tail(&dll, "somon");
    // print_dll(&dll);
    // int x;
    // x = contains(dll, "nu");
    // printf("%d", x);
    return 0;
}

struct node* new_node(char* data) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

struct double_linked_list new_dll() {
    return (struct double_linked_list) {};
}

void print_node(struct node* node) {
    printf("%s ", node->data);
}

void print_dll(struct double_linked_list* dll) {
    for(struct node* i = dll->head; i != NULL; i = i->next) {
        print_node(i);
    }
}

void push_tail(struct double_linked_list* dll, char* data) {
    struct node* node = new_node(data);
    if(dll->size == 0) {
        dll->head = node;
        dll->tail = node;
    }
    else {
        dll->tail->next = node;
        node->prev = dll->tail;
        dll->tail = node;
    }
    dll->size++;
}

char* remove_tail(struct double_linked_list* dll) {
    struct node* node;
    switch (dll->size) {
        case 0:
            return NULL;

        case 1:
            node = dll->head;
            dll->head = dll->tail = NULL;
            break;

        default:
            node = dll->tail;
            dll->tail = dll->tail->prev;
            dll->tail->next = NULL;
            break;
    }
    dll->size--;
    return node->data;
}

struct node* find_first(struct double_linked_list dll, char* data) {
    for(struct node* i = dll.head; i != NULL; i = i->next) {
        if(strcmp(i->data, data) == 0) {
            return i;
        }
    }
    return NULL;
}

char* remove_first(struct double_linked_list* dll, char* data) {
    struct node* node = find_first(*dll, data);
    struct node* prev = node->prev;
    struct node* next = node->next;
    char* removed_data;

    //case 1: no node matches the search criteria
    if(node == NULL) {
        return NULL;
    }
    //case 2: head matches the search criteria
    else if(prev == NULL) {
        next->prev = NULL;
        dll->head = next;
        }
    //case 3: tail matches the search criteria
    else if(next == NULL) {
        prev->next = NULL;
        dll->tail = prev;
    }
    //case 4: inned node matches the search criteria
    else {
        prev->next = next;
        next->prev = prev;
    }
    removed_data = node->data;
    node->data = NULL;
    node->next = NULL;
    node->prev = NULL;
    free(node);
    node = NULL;
    dll->size--;
    return removed_data;
}

void free_node(struct node** node) {
    (**node).data = NULL;
    (**node).next = NULL;
    (**node).prev = NULL;
    free(*node);
    *node = NULL;
}

void free_all_nodes(struct double_linked_list* dll) {
    struct node* node;
    for(struct node* i = dll->head; i != NULL;) {
        node = i;
        i = i->next;
        free_node(&node);
    }
    dll->size = 0;
    dll->head = NULL;
    dll->tail = NULL;
}

void push_head(struct double_linked_list* dll, char* data) {
    struct node* node = new_node(data);
    if(dll->size == 0) {
        dll->head = node;
        dll->tail = node;
    }
    else {
        dll->head->prev = node;
        node->next = dll->head;
        dll->head = node;
    }
    dll->size++;
}

char* remove_head(struct double_linked_list* dll) {
    struct node* node;
    switch (dll->size) {
        case 0:
            return NULL;
        
        case 1:
            node = dll->head;
            dll->head = dll->tail = NULL;
            break;

        default:
            node = dll->head;
            node->next = NULL; 
            dll->head = dll->head->next;
            dll->head->prev = NULL;
            break;
    }
    dll->size--;
    return node->data;
}

int contains(struct double_linked_list dll, char* data) {
    if(find_first(dll, data) != NULL) {
        return 1;
    }
    else return 0;
}

void add_after(struct double_linked_list* dll, struct node* prev_node, char* data) {
    struct node* added_node = new_node(data);
    added_node->next = prev_node->next;
    added_node->prev = prev_node;
    prev_node->next = added_node;
    if(added_node->next != NULL) {
        added_node->next->prev = added_node;
    }
    else {
        dll->tail = added_node;
    }
}
