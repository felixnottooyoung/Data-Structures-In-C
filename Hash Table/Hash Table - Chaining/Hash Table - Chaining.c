#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 26

struct Data{
    char word[101];
    struct Data *next;
};

struct Data *hashTableHead[SIZE] = {NULL};
struct Data *hashTableTail[SIZE] = {NULL};

int hashFunction(char word[]){
    int len = strlen(word);

    int ascii_sum = 0;
    for(int i=0;i<len;i++){
        ascii_sum+=word[i];
    }

    return ascii_sum % SIZE;
}

void insert(char inputWord[]){
    int key = hashFunction(inputWord);

    struct Data *current = hashTableHead[key];
    while(current != NULL){
        if(strcmp(inputWord, current->word) == 0){
            return;
        }
        current = current->next;
    }

    struct Data *node = (struct Data *)malloc(sizeof(struct Data));
    strcpy(node->word, inputWord);
    node->next = NULL;

    if(hashTableHead[key] == NULL){
        hashTableHead[key] = hashTableTail[key] = node;
    }
    else{
        hashTableTail[key]->next = node;
        hashTableTail[key] = node;
    }
}

void search(char targetWord[]){
    int key = hashFunction(targetWord);

    if(hashTableHead[key] == NULL){
        printf("The word \"%s\" is not found inside the hash table\n", targetWord);
    }
    else{
        int isFound = 0, chain_order = 1;
        struct Data *current = hashTableHead[key];
        while(current != NULL){
            if(strcmp(targetWord, current->word) == 0){
                printf("Word \"%s\" is found. Here are the details :\n", current->word);
                printf("Key : %d\n", key);
                printf("Chain order : %d\n", chain_order);
                isFound = 1;
                break;
            }
            current = current->next;
            chain_order++;
        }

        if(!isFound){
            printf("The word \"%s\" is not found inside the hash table\n", targetWord);
        }
    }
}

void viewHashTable(){
    for(int i=0;i<SIZE;i++){
        if(hashTableHead[i] == NULL){
            printf("[%02d] : NULL\n", i);
        }
        else{
            printf("[%02d] : %s", i, hashTableHead[i]->word);

            struct Data *current = hashTableHead[i]->next;
            while(current != NULL){
                printf(" -> %s", current->word);
                current = current->next;
            }
            printf("\n");
        }
    }
}

int main(){
    insert("define");
	insert("float");
	insert("exp");
	insert("char");
	insert("atan");
	insert("ceil");
	insert("floor");
	insert("acos");

	viewHashTable();

	printf("\nTest 1 for search :\n");
	search("acos");
	printf("\nTest 2 for search :\n");
	search("Acos");
	printf("\nTest 3 for search :\n");
	search("define");
	printf("\nTest 4 for search :\n");
	search("exp");
    return 0;
}
