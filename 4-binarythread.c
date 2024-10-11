#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
	int data;
	struct tree_node* right, * left;
}TreeNode;

typedef struct ThreadTree {
	int data;
	struct tree_node* right, * left;
	int is_thread;
}ThreadTree;

TreeNode* new_node(int key) {
	TreeNode* temp;
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = key;
	temp->right = temp->left = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
	if (root == NULL) return new_node(key);
	if (root->data == key) return root;
	else if (root->data > key)
		root->left = insert_node(root->left, key);
	else
		root->right = insert_node(root->right, key);
	return root;
}

TreeNode* GenerateBinaryTree(int inputData[]) {
	TreeNode* root = NULL;//입력
	for (int i = 0; i < 15 ; i++) {
		int key = inputData[i];
		root=insert_node(root, key);
	}
	return root;
}

void BinaryTreeInOrder(TreeNode* root) {
	if (root != NULL) {
		BinaryTreeInOrder(root->left);
		printf("%d ", root->data);
		BinaryTreeInOrder(root->right);
	}
}

//ThreadTree

ThreadTree* New_node(int key) {
	ThreadTree* temp;
	temp = (ThreadTree*)malloc(sizeof(ThreadTree));
	temp->data = key;
	temp->right = temp->left = NULL;
	temp->is_thread = 0;
	return temp;
}

ThreadTree* Insert_node(ThreadTree* root, int key) {
	if (root == NULL) return New_node(key);
	if (root->data == key) return root;
	else if (root->data > key)
		root->left = Insert_node(root->left, key);
	else
		root->right = Insert_node(root->right, key);
	return root;
}

ThreadTree* search_bst(ThreadTree* root, int key) {
	if (root == NULL) return NULL;
	else {
		if (root->data == key)
			return root;
		else if (root->data > key)
			return search_bst(root->left, key);
		else
			return search_bst(root->right, key);
	}
}

void connect_thread(ThreadTree* root) {
	ThreadTree* temp = NULL;
	ThreadTree* temp2 = NULL;

	temp = search_bst(root, 2);
	temp2 = search_bst(root, 3);
	temp->is_thread = 1;
	temp->right = temp2;

	temp = search_bst(root, 3);
	temp2 = search_bst(root, 4);
	temp->is_thread = 1;
	temp->right = temp2;

	temp = search_bst(root, 5);
	temp2 = search_bst(root, 6);
	temp->is_thread = 1;
	temp->right = temp2;

	temp = search_bst(root, 8);
	temp2 = search_bst(root, 9);
	temp->is_thread = 1;
	temp->right = temp2;

	temp = search_bst(root, 11);
	temp2 = search_bst(root, 12);
	temp->is_thread = 1;
	temp->right = temp2;

	temp = search_bst(root, 12);
	temp2 = search_bst(root, 13);
	temp->is_thread = 1;
	temp->right = temp2;

	temp = search_bst(root, 14);
	temp2 = search_bst(root, 15);
	temp->is_thread = 1;
	temp->right = temp2;
}

ThreadTree* GenerateThreadTree(int inputData[]) {
	ThreadTree* root = NULL;
	for (int i = 0; i < 15; i++) {
		int key = inputData[i];
		root = insert_node(root, key);
	}
	connect_thread(root);
	return root;
}

ThreadTree* find_successor(ThreadTree* p) {
	ThreadTree* q = p->right;
	if (q == NULL || p->is_thread == 1)
		return q;

	while (q->left != NULL) q = q->left;
	return q;
}

void ThreadTreeInOrder(ThreadTree* root) {
	ThreadTree* q = root;
	while (q->left) q = q->left;  // 가장 왼쪽 노드로 이동
	do {
		printf("%d ", q->data);
		q = find_successor(q);  // 후계자를 찾음
	} while (q);
}

int main() {
	int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
	TreeNode* root = GenerateBinaryTree(inputData);
	printf("Binary tree inorder: ");
	BinaryTreeInOrder(root);

	printf("\nThread tree inorder: ");
	ThreadTree* troot = GenerateThreadTree(inputData);
	ThreadTreeInOrder(troot);

	free(root);
	free(troot);
	return 0;
}