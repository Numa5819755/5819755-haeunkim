#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
}TreeNode;

void GenerateArrayTree(int* tree) {
    int list[15] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };
    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
    printf("\n");
}

void ArrayPreOder(int* tree) {
    int stack[15];
    int top = -1; 

    stack[++top] = 0;

    while (top >= 0) {
        int index = stack[top--];

        if (index >= 15) 
            continue;  

        printf("%d ", tree[index]);

        if (index * 2 + 2 < 15) {
            stack[++top] = index * 2 + 2;
        }

        if (index * 2 + 1 < 15) {
            stack[++top] = index * 2 + 1;
        }
    }
    printf("\n");
}

void ArrayInOder(int* tree) {
    int stack[15];
    int top = -1;

    int index = 0;
    int current = 0; 

    while (top >= 0 || current < 15) {
        while (current < 15) {
            stack[++top] = current; 
            current = current * 2 + 1;  
        }
        if (top >= 0) {
            current = stack[top--]; 
            printf("%d ", tree[current]); 

            current = current * 2 + 2;
        }
    }
    printf("\n");
}

void ArrayPostOder(int* tree) {
    int stack1[15];
    int stack2[15];
    int top1 = -1; 
    int top2 = -1; 

    stack1[++top1] = 0;

    while (top1 >= 0) {
        int index = stack1[top1--];
        stack2[++top2] = index;

        if (index * 2 + 1 < 15) {
            stack1[++top1] = index * 2 + 1;
        }
        if (index * 2 + 2 < 15) {
            stack1[++top1] = index * 2 + 2;
        }
    }

    while (top2 >= 0) {
        int index = stack2[top2--];
        printf("%d ", tree[index]);
    }
    printf("\n");
    printf("\n");
}

void ArrayOders(int* tree) {
    ArrayPreOder(tree);
    ArrayInOder(tree);
    ArrayPostOder(tree);
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
    newnode->left = newnode->right = NULL;
    newnode->data = data;
    if (direction == 0) {
        node->left = newnode;
    }
    else if (direction == 1) {
        node->right = newnode;
    }
    else {
        printf("error:direction");
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

void LinkPreOder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        LinkPreOder(root->left);
        LinkPreOder(root->right);
        if (root->data == 15)
            printf("\n");
    }
}
void LinkInOder(TreeNode* root) {
    if (root != NULL) {
        LinkInOder(root->left);
        printf("%d ", root->data);
        LinkInOder(root->right);
        if (root->data == 15)
            printf("\n");
    }
}
void LinkPostOder(TreeNode* root) {
    if (root != NULL) {
        LinkPostOder(root->left);
        LinkPostOder(root->right);
        printf("%d ", root->data);
        if (root->data == 1)
            printf("\n");
    }
}
void LinkOders(TreeNode* root) {
    LinkPreOder(root);
    LinkInOder(root);
    LinkPostOder(root);
}

int main() {
    int arr[15];
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;

    GenerateArrayTree(arr);
    GenerateLinkTree(root);
    
    ArrayOders(arr);
    LinkOders(root);

    return 0;
}