#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 26

struct Data{
    char word[101];
};

struct Data *hashTable[SIZE] = {NULL};

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

    while(hashTable[key] != NULL){
        if(strcmp(inputWord, hashTable[key]->word) == 0){
            return;
        }
        key = (key + 1) % SIZE;
    }

    hashTable[key] = (struct Data *)malloc(sizeof(struct Data));
    strcpy(hashTable[key]->word, inputWord);
}

void search(char targetWord[]){
    int key = hashFunction(targetWord);

    int isFound = 0, originalKey = key;
    while(hashTable[key] != NULL){
        if(strcmp(targetWord, hashTable[key]->word) == 0){
            printf("Word \"%s\" is found. The key is : %d\n", hashTable[key]->word, key);
            isFound = 1;
            break;
        }
        key = (key + 1) % SIZE;
        if(key == originalKey){
            break;
        }
    }

    if(!isFound){
        printf("The word \"%s\" is not found inside the hash table\n", targetWord);
    }
}

void viewHashTable(){
    for(int i=0;i<26;i++){
        if(hashTable[i] == NULL){
            printf("[%02d] : NULL\n", i);
        }
        else{
            printf("[%02d] : %s\n", i, hashTable[i]->word);
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
