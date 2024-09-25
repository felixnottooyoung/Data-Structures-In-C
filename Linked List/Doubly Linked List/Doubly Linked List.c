#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    int value;
    struct Node *next, *prev;
};

struct Node *head = NULL;
struct Node *tail = NULL;

struct Node *createNode(int inputValue){
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = inputValue;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

void pushHead(int inputValue){
    struct Node *node = createNode(inputValue);

    if(head == NULL){
        head = tail = node;
    }
    else{
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void pushTail(int inputValue){
    struct Node *node = createNode(inputValue);

    if(head == NULL){
        head = tail = node;
    }
    else{
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void pushAfterValue(int inputValue, int afterValue){
    if(head != NULL){
        if(tail->value == afterValue){
            pushTail(inputValue);
        }
        else{
            struct Node *node = createNode(inputValue);

            struct Node *current = head;
            while(current != NULL && current->value != afterValue){
                current = current->next;
            }

            if(current != NULL){
                node->next = current->next;
                current->next->prev = node;
                current->next = node;
                node->prev = current;
            }
        }
    }
}

void popHead(){
    if(head != NULL){
        if(head == tail){
            free(head);
            head = tail = NULL;
        }
        else{
            struct Node *temp = head;
            head = head->next;
            head->prev = NULL;
            free(temp);
        }
    }
}

void popTail(){
    if(head != NULL){
        if(head == tail){
            free(head);
            head = tail = NULL;
        }
        else{
            struct Node *temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
    }
}

void popMid(int targetValue){
    if(head != NULL){
        if(head->value == targetValue){
            popHead();
        }
        else if(tail->value == targetValue){
            popTail();
        }
        else{
            struct Node *current = head;

            while(current != NULL && current->value != targetValue){
                current = current->next;
            }

            if(current != NULL){
                current->next->prev = current->prev;
                current->prev->next = current->next;
                free(current);
            }
        }
    }
}

void popAll(){
    while(head != NULL){
        popHead();
    }
}

void printList(){
    printf("NULL  ---  ");

    struct Node *current = head;
    while(current != NULL){
        printf("%d  ---  ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int main(){
    pushTail(-10);
    pushTail(-20);
    pushTail(-30);
    pushTail(-50);
    pushTail(-60);
    pushAfterValue(-40, -30);
    pushHead(0);
    printList();
    popMid(-30);
    printList();
    return 0;
}
