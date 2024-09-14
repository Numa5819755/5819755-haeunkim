#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* link;
} StackNode;

StackNode* init(TreeNode* node) {
    StackNode* stacknode = (StackNode*)malloc(sizeof(StackNode));
    stacknode->treeNode = node;
    stacknode->link = NULL;
    return stacknode;
}

int isEmpty(StackNode* top) {
    return top == NULL;
}

void push(StackNode** top, TreeNode* node) {
    printf("push(%d) ", node->data);
    StackNode* stacknode = init(node);
    stacknode->link = *top;
    *top = stacknode;
}

TreeNode* pop(StackNode** top) {
    if (isEmpty(*top)) return NULL;
    StackNode* temp = *top;
    *top = (*top)->link;
    TreeNode* node = temp->treeNode;
    printf("pop(%d) ", node->data);
    free(temp);
    return node;
}

void visit(TreeNode* node) {
    printf("visit(%d)\n", node->data);
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    if (direction == 0)
        node->left = newNode;
    else
        node->right = newNode;
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

void LinkPreOrder(TreeNode* root) {
    StackNode* stack = NULL;
    push(&stack, root);

    printf("전위 순회의 출력 예\n");
    while (!isEmpty(stack)) {
        TreeNode* currentNode = pop(&stack);
        visit(currentNode);
        if (currentNode->right)
            push(&stack, currentNode->right);
        if (currentNode->left)
            push(&stack, currentNode->left);
    }
    printf("\n");
}

void LinkPostOrder(TreeNode* root) {
    if (root == NULL) return;

    StackNode* stack1 = NULL;
    StackNode* stack2 = NULL;
    push(&stack1, root);

    printf("후위 순회의 출력 예\n");
    while (!isEmpty(stack1)) {
        TreeNode* currentNode = pop(&stack1);
        push(&stack2, currentNode);
        if (currentNode->left)
            push(&stack1, currentNode->left);
        if (currentNode->right)
            push(&stack1, currentNode->right);
    }
    while (!isEmpty(stack2)) {
        TreeNode* currentNode = pop(&stack2);
        visit(currentNode);
    }
    printf("\n");
}

void LinkInOrder(TreeNode* root) {
    StackNode* stack = NULL;
    TreeNode* currentNode = root;

    printf("중위 순회의 출력 예\n");
    while (!isEmpty(stack) || currentNode != NULL) {
        if (currentNode != NULL) {
            push(&stack, currentNode);
            currentNode = currentNode->left;
        }
        else {
            currentNode = pop(&stack);
            visit(currentNode);
            currentNode = currentNode->right;
        }
    }
    printf("\n");
}

void LinkOrders(TreeNode* root) {
    LinkPreOrder(root);
    LinkInOrder(root);
    LinkPostOrder(root);
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;


    GenerateLinkTree(root);
    LinkOrders(root);

    return 0;
}