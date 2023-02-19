#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char* data;
    struct node* next;
};

struct queue {
    struct node* head;
    struct node* tail;
    int size;
};

struct node* new_node(char* data);
void print_node(struct node node);
struct queue new_queue();
void print_queue(struct queue q);
void push(struct queue* q, char* data);
char* pop(struct queue* q);
char* peek(struct queue* q);

int main() {
    struct queue q = new_queue();
    push(&q, "Azi");
    push(&q, "nu");
    push(&q, "mananc");
    push(&q, "peste");
    push(&q, "proaspat");
    print_queue(q);
    pop(&q);
    printf("Capul cozii este: %s\n", peek(&q));
    print_queue(q);
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

struct queue new_queue() {
    return (struct queue) {};
}

void print_queue(struct queue q) {
    struct node* node;
    for(node = q.head; node != NULL; node = node->next) {
        printf("%s ", node->data);
    }
    printf("\n");
}

void push(struct queue* q, char* data) {
    struct node* node = new_node(data);
    if(q->size == 0) {
        q->head = node;
        q->tail = node;
    }
    else {
        q->tail->next = node;
        q->tail = node;
    }
    q->size++;
}

char* pop(struct queue* q) {
    struct node* node;
    char* data; 
    switch (q->size) {
        case 0:
            return NULL;
        case 1:
            node = q->head;
            q->head = NULL;
            q->tail = NULL;
            break;
       default:
            node = q->head;
            q->head = node->next;
            node->next = NULL;
    }
    data = node->data;
    free(node);
    node = NULL;
    q->size--;
    return data;
}

char* peek(struct queue* q) {
    return q->head->data;
}
