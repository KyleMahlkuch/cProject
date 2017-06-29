#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;
 
typedef void (*callback)(node* data);

node* create(int data,node* next) {
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = next;
 
    return new_node;
}

typedef struct linkedList {
    struct node* head; 
    int size;
} linkedList;

linkedList* list_create() {
    linkedList* new_list = (linkedList*)malloc(sizeof(linkedList));
    new_list->size = 0; 
    return new_list;
}

void insert(int data, linkedList* the_list) {
    struct node *prev, *curr, *a;
    curr = the_list->head;
    prev = NULL;
    a = create(data, NULL);

    if (curr == NULL) {
        the_list->head = a;
        the_list->size++;
        return;
    }
    if (curr->data > a->data){
        a->next = the_list->head;
        the_list->head = a;
        the_list->size++;
        return;
    }

    while (curr != NULL && curr->data < a->data) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        prev->next = a;
        a->next = curr;
        the_list->size++;
        return;
    }

    if (a->data != curr->data) {
        prev->next = a;
        a->next = curr;
        the_list->size++;
    } 
}

void printList(linkedList* the_list) {
    struct node *a;
    a = the_list->head;
    printf("length: %d \n", the_list->size);
    while(a != NULL) {
        printf("%d", a->data);
        if (a->next != NULL) {
            printf(", ");
        }
        a = a->next;
    }
    printf("\n");

}