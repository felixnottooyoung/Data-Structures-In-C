#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Item{
    int value;
    char priority_class[101];
    struct Item *next, *prev;
};

struct Item *front = NULL;
struct Item *back = NULL;

struct Item *createItem(int inputValue, char priority_class[]){
    struct Item *newItem = (struct Item *)malloc(sizeof(struct Item));
    newItem->value = inputValue;
    strcpy(newItem->priority_class, priority_class);
    newItem->next = newItem->prev = NULL;
    return newItem;
}

int isEmpty(){
    return front == NULL;
}

void enqueue(int inputValue, char priority_class[]){
    struct Item *current = createItem(inputValue, priority_class);

    if(isEmpty()){
        front = back = current;
    }
    else{
        if(strcmp(priority_class, "Regular") == 0){
            back->next = current;
            current->prev = back;
            back = current;
        }
        else if(strcmp(priority_class, "VIP") == 0){
            current->next = front;
            front->prev = current;
            front = current;
        }
    }
}

void dequeue(){
    if(isEmpty()){
        printf("The queue is empty!!!\n");
    }
    else{
        if(front == back){
            front = back = NULL;
        }
        else{
            struct Item *temp = front;
            front = front->next;
            front->prev = NULL;
            free(temp);
        }
    }
}

void peek(){
    if(isEmpty()){
        printf("The queue is empty!!!\n");
    }
    else{
        printf("The front's value is %d\n", front->value);
    }
}

void view(){
    if(isEmpty()){
        printf("The queue is empty!!!\n");
    }
    else{
        printf("  Front\n");
        struct Item *temp = front;
        while(temp != NULL){
            printf("|  %d  |\n", temp->value);
            temp = temp->next;
        }
        printf("  Back\n");
    }
}

int main(){
    enqueue(10, "VIP");
    enqueue(20, "Regular");
    enqueue(30, "VIP");
    enqueue(40, "Regular");
    enqueue(50, "VIP");
    enqueue(60, "Regular");

    printf("Before dequeue :\n\n"); view();
    peek();

    dequeue(); printf("\n=========================\n");

    printf("\nAfter dequeue :\n\n"); view();
    peek();
    return 0;
}
