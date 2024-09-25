#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    int value;
    struct Node *next;
};

struct Node *head = NULL;
struct Node *tail = NULL;

struct Node *createNode(int inputValue){
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = inputValue;
    newNode->next = NULL;
    return newNode;
}

void pushHead(int inputValue){
    struct Node *node = createNode(inputValue);

    if(head == NULL){
        head = tail = node;
    }
    else{
        node->next = head;
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
                current->next = node;
            }
        }
    }
}

void popHead(){
    if(head != NULL){
        if(head == tail){
            head = tail = NULL;
        }
        else{
            struct Node *temp = head;
            head = head->next;
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
            struct Node *current = head;
            while(current->next != tail){
                current = current->next;
            }

            free(current->next);
            current->next = NULL;
            tail = current;
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

            while(current->next != NULL && current->next->value != targetValue){
                current = current->next;
            }

            if(current->next != NULL){
                struct Node *temp = current->next;
                current->next = current->next->next;
                free(temp);
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
