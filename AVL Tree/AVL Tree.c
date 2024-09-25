#include <stdio.h>
#include <stdlib.h>

struct Node{
    int value;
    int height;
    struct Node *left, *right;
};

struct Node *root = NULL;

struct Node *createNode(int inputValue){
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = inputValue;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int getMax(int a, int b){
    return (a > b) ? a : b;
}

int getHeight(struct Node *current){
    return (current == NULL) ? 0 : current->height;
}

int getBalanceFactor(struct Node *current){
    return (current == NULL) ? 0 : (getHeight(current->left) - getHeight(current->right));
}

struct Node *rightRotation(struct Node *current){
    struct Node *child = current->left;
    struct Node *grandChild = child->right;

    child->right = current;
    current->left = grandChild;

    current->height = getMax(getHeight(current->left), getHeight(current->right)) + 1;
    child->height = getMax(getHeight(child->left), getHeight(child->right)) + 1;

    return child;
}

struct Node *leftRotation(struct Node *current){
    struct Node *child = current->right;
    struct Node *grandChild = child->left;

    child->left = current;
    current->right = grandChild;

    current->height = getMax(getHeight(current->left), getHeight(current->right)) + 1;
    child->height = getMax(getHeight(child->left), getHeight(child->right)) + 1;

    return child;
}

struct Node *insertNode(struct Node *current, int inputValue){
    if(current == NULL){
        return createNode(inputValue);
    }

    if(inputValue < current->value){
        current->left = insertNode(current->left, inputValue);
    }
    else if(inputValue > current->value){
        current->right = insertNode(current->right, inputValue);
    }
    else{
        return current;
    }

    current->height = getMax(getHeight(current->left), getHeight(current->right)) + 1;
    int balanceFactor = getBalanceFactor(current);

    //Left-Left
    if(balanceFactor > 1 && inputValue < current->left->value){
        return rightRotation(current);
    }
    //Right-Right
    if(balanceFactor < -1 && inputValue > current->right->value){
        return leftRotation(current);
    }
    //Left-Right
    if(balanceFactor > 1 && inputValue > current->left->value){
        current->left = leftRotation(current->left);
        return rightRotation(current);
    }
    //Right-Left
    if(balanceFactor < -1 && inputValue < current->right->value){
        current->right = rightRotation(current->right);
        return leftRotation(current);
    }

    return current;
}

struct Node *findMin(struct Node *current){
    struct Node *temp = current;
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

struct Node *findMax(struct Node *current){
    struct Node *temp = current;
    while(temp->right != NULL){
        temp = temp->right;
    }
    return temp;
}

struct Node *deleteNode(struct Node *current, int targetValue){
    if(current == NULL){
        return current;
    }

    if(targetValue < current->value){
        current->left = deleteNode(current->left, targetValue);
    }
    else if(targetValue > current->value){
        current->right = deleteNode(current->right, targetValue);
    }
    else{
        //0 children or 1 child
        if(current->left == NULL){
            struct Node *temp = current->right;
            free(current);
            return temp;
        }
        else if(current->right == NULL){
            struct Node *temp = current->left;
            free(current);
            return temp;
        }

        //2 children
        struct Node *temp = findMin(current->right);
        current->value = temp->value;
        current->right = deleteNode(current->right, temp->value);
    }

    if(current == NULL){
        return current;
    }

    current->height = getMax(getHeight(current->left), getHeight(current->right)) + 1;
    int balanceFactor = getBalanceFactor(current);

    //Left-Left
    if(balanceFactor > 1 && getBalanceFactor(current->left) >= 0){
        return rightRotation(current);
    }
    //Right-Right
    if(balanceFactor < -1 && getBalanceFactor(current->right) <= 0){
        return leftRotation(current);
    }
    //Left-Right
    if(balanceFactor > 1 && getBalanceFactor(current->left) < 0){
        current->left = leftRotation(current->left);
        return rightRotation(current);
    }
    //Right-Left
    if(balanceFactor < -1 && getBalanceFactor(current->right) > 0){
        current->right = rightRotation(current->right);
        return leftRotation(current);
    }

    return current;
}

void searchNode(struct Node *current, int targetValue){
    if(current == NULL){
        printf("%d is not found inside the AVL Tree\n", targetValue);
        return;
    }

    if(targetValue < current->value){
        searchNode(current->left, targetValue);
    }
    else if(targetValue > current->value){
        searchNode(current->right, targetValue);
    }
    else{
        printf("%d is found inside the AVL Tree\n", current->value);
        return;
    }
}

void preOrder(struct Node *current){
    if(current != NULL){
        printf("%d ", current->value);
        preOrder(current->left);
        preOrder(current->right);
    }
}

void inOrder(struct Node *current){
    if(current != NULL){
        inOrder(current->left);
        printf("%d ", current->value);
        inOrder(current->right);
    }
}

void postOrder(struct Node *current){
    if(current != NULL){
        postOrder(current->left);
        postOrder(current->right);
        printf("%d ", current->value);
    }
}

void viewAVLTree(struct Node *current, int level){
    if(current != NULL){
        viewAVLTree(current->right, level+1);
        for(int i=0;i<level;i++){
            printf("     ");
        }
        printf("%d\n", current->value);
        viewAVLTree(current->left, level+1);
    }
}

int main(){
    root = insertNode(root, 1);
    root = insertNode(root, 2);
    root = insertNode(root, 3);
    root = insertNode(root, 4);
    root = insertNode(root, 5);
    root = insertNode(root, 6);
    root = insertNode(root, 7);
    root = insertNode(root, 8);
    root = insertNode(root, 9);
    root = insertNode(root, 10);

    printf("Before deletion :\n");
    printf("Pre Order : "); preOrder(root); printf("\n");
    printf("In Order : "); inOrder(root); printf("\n");
    printf("Post Order : "); postOrder(root); printf("\n\n");
    printf("The AVL Tree :\n"); viewAVLTree(root, 0); printf("\n");
    searchNode(root, 4);
    searchNode(root, 3);

    root = deleteNode(root, 4);

    printf("\nAfter deletion :\n");
    printf("Pre Order : "); preOrder(root); printf("\n");
    printf("In Order : "); inOrder(root); printf("\n");
    printf("Post Order : "); postOrder(root); printf("\n\n");
    printf("The AVL Tree :\n"); viewAVLTree(root, 0); printf("\n");
    searchNode(root, 4);
    searchNode(root, 3);
    return 0;
}
