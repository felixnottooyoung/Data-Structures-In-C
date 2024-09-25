#include <stdio.h>

#define MAX_SIZE 10

int items[MAX_SIZE];
int top = -1;

// Initially initializes every value to -1 to indicate empty value
void initializeToMinusOne(){
    for(int i=0;i<MAX_SIZE;i++){
        items[i] = -1;
    }
}

int isFull(){
    return top == MAX_SIZE-1;
}

int isEmpty(){
    return top == -1;
}

void push(int value){
    if(isFull()){
        printf("The stack is full!!!\n");
    }
    else{
        items[++top] = value;
    }
}

void pop(){
    if(isEmpty()){
        printf("The stack is empty!!!\n");
    }
    else{
        items[top--] = -1;
    }
}

void peek(){
    if(isEmpty()){
        printf("The stack is empty!!!\n");
    }
    else{
        printf("The top's value is : %d\n", items[top]);
    }
}

void view(){
    if(isEmpty()){
        printf("The stack is empty!!!\n");
    }
    else{
        for(int i=top;i>=0;i--){
            printf("|  %d  |\n", items[i]);
            printf("========\n");
        }
    }
}

int main(){
    initializeToMinusOne();

    push(10);
    push(20);
    push(30);
    push(40);
    push(50);

    printf("Before pop :\n\n"); view();
    peek();

    pop(); printf("\n=========================\n");

    printf("\nAfter pop :\n\n"); view();
    peek();
    return 0;
}
