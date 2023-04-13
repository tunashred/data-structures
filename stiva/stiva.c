#include <stdio.h>
#include <stdlib.h>

struct node {
    char* data;
    struct node* prev;
    struct node* next;
};

struct stack {
    struct node* head;
    struct node* tail;
    int size;
};

struct node* new_node(char* data);
void print_node(struct node node);
struct stack new_stack();
void print_stack(struct stack s);
void push(struct stack* s, char* data);
char* pop(struct stack* s);

int main() {
    struct stack s = new_stack();
    push(&s, "azi");
    push(&s, "nu");
    push(&s, "mananc");
    push(&s, "peste");
    push(&s, "proaspat");
    print_stack(s);
    pop(&s);
    print_stack(s);
    pop(&s);
    pop(&s);
    pop(&s);
    push(&s, "mananc");
    push(&s, "peste");
    push(&s, "proaspat");
    print_stack(s);

    return 0;
}

struct node* new_node(char* data) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void print_node(struct node node) {
    printf("%s", node.data);
}

struct stack new_stack() {
    return (struct stack) {};
}

void print_stack(struct stack s) {
    struct node* node;
    for(node = s.head; node != NULL; node = node->next) {
        printf("%s ", node->data);
    }
    printf("\n");
}

void push(struct stack* s, char* data) {
    struct node* node = new_node(data);
    if(s->size == 0) {
        s->head = node;
        s->tail = node;
    }
    else {
        s->tail->next = node;
        node->prev = s->tail;
        s->tail = node;
    }
    s->size++;
}

char* pop(struct stack* s) {
    char* data;
    struct node* node;
    switch(s->size) {
        case 0:
            return NULL;
        case 1:
            node = s->head;
            s->head = NULL;
            s->tail = NULL;
            break;
        default:
            node = s->tail;
            s->tail = s->tail->prev;
            s->tail->next = NULL;
    }
    data = node->data;
    free(node);
    s->size--;
    return data;
}
