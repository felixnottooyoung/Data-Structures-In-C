#include <stdio.h>
#include <stdlib.h>

struct Item{
    int value;
    struct Item *next, *prev;
};

struct Item *front = NULL;
struct Item *back = NULL;

struct Item *createItem(int inputValue){
    struct Item *newItem = (struct Item *)malloc(sizeof(struct Item));
    newItem->value = inputValue;
    newItem->next = newItem->prev = NULL;
    return newItem;
}

int isEmpty(){
    return front == NULL;
}

void enqueue(int inputValue){
    struct Item *current = createItem(inputValue);

    if(isEmpty()){
        front = back = current;
    }
    else{
        back->next = current;
        current->prev = back;
        back = current;
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
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);

    printf("Before dequeue :\n\n"); view();
    peek();

    dequeue(); printf("\n=========================\n");

    printf("\nAfter dequeue :\n\n"); view();
    peek();
    return 0;
}
