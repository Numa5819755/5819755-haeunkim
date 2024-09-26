#include <stdio.h>
#include <stdlib.h>
//typedef
typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

typedef TreeNode* element;

typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct {
	QueueNode* front, * rear;
} LinkedQueueType;

//fx queue
void init(LinkedQueueType* q) {
	q->front = q->rear = NULL;
}

int is_empty(LinkedQueueType* q) {
	return (q->front == NULL);
}

void enqueue(LinkedQueueType* q, element data)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = data; 		
	temp->link = NULL; 		
	if (is_empty(q)) { 	
		q->front = temp;
		q->rear = temp;
	}
	else { 		
		q->rear->link = temp;  
		q->rear = temp;
	}
}

element dequeue(LinkedQueueType* q)
{
	QueueNode* temp = q->front;
	element data;
	if (is_empty(q)) {		
		fprintf(stderr, "is_empty\n");
		exit(1);
	}
	else {
		data = temp->data; 	
		q->front = q->front->link; 
		if (q->front == NULL) 	
			q->rear = NULL;
		free(temp); 		
		return data; 		
	}
}
//end
//fx
void placeNode(TreeNode* node, int direction, int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	if (direction == 0)
		node->left = newNode;
	else
		node->right = newNode;
}

void GenerateLinkTree(TreeNode* root) {
	placeNode(root, 0, 2);
	placeNode(root, 1, 9);
	placeNode(root->left, 0, 3);
	placeNode(root->left, 1, 5);
	placeNode(root->left->left, 0, 4);
	placeNode(root->left->left, 1, 6);
	placeNode(root->left->right, 0, 7);
	placeNode(root->left->right, 1, 8);
	placeNode(root->right, 0, 10);
	placeNode(root->right, 1, 13);
	placeNode(root->right->left, 0, 11);
	placeNode(root->right->left, 1, 12);
	placeNode(root->right->right, 0, 14);
	placeNode(root->right->right, 1, 15);
}
//fx 
void GetSumOfNodes(TreeNode* root) {
	int node_sum = 0;
	LinkedQueueType q;
	TreeNode* ptr = root;
	init(&q);

	if (root == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		node_sum += ptr->data;
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
	printf("Sum of nodes: %d\n", node_sum);
	return;
}

void GetNumberOfNodes(TreeNode* root) {
	int node_count = 0;
	LinkedQueueType q;
	TreeNode* ptr = root;
	init(&q);

	if (root == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);

		node_count += 1;
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
	printf("Number of nodes: %d\n", node_count);
	return;
}

int GetHeightOfNodesHelper(TreeNode* root) {
	if (root == NULL)
		return 0;
	else {
		int leftHeight = GetHeightOfNodesHelper(root->left);
		int rightHeight = GetHeightOfNodesHelper(root->right);
		return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
	}
}

void GetHeightOfNodes(TreeNode* root) {
	int height = GetHeightOfNodesHelper(root);
	printf("Height of tree: %d\n", height);
}

void GetNumberOfLeafNodes(TreeNode* root) {
	int leaf_count = 0;
	LinkedQueueType q;
	TreeNode* ptr = root;
	init(&q);

	if (root == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		if (ptr->left == NULL && ptr->right == NULL)
			leaf_count += 1;
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
	printf("Number of leaf nodes: %d\n", leaf_count);
	return;
}
//end

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;

	GenerateLinkTree(root);

	GetSumOfNodes(root);
	GetNumberOfNodes(root);
	GetHeightOfNodes(root);
	GetNumberOfLeafNodes(root);

	return 0;
}
