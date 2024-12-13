#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//전역변수
int compareCount=0;
int searchCount =0;
//구조체 선언
typedef struct Node {
	int key;
	struct Node* left, * right;
	int height;
} Node;


//함수 구현

//test
void inOrder(Node* root) {
	if (root == NULL) return;
	if (root->left != (Node*)NULL) inOrder(root->left);
	printf("%2d[%d] ", root->key, root->height);
	if (root->right != (Node*)NULL) inOrder(root->right);
}

//AVL과 Bin 공통: 탐색 함수
//search 관련 함수
void searchNode(Node* root, int key) {
	while (root != NULL) {
		if (key == root->key) {
			compareCount++;
			break; // 키를 찾았을 경우 종료
		}
		else if (key < root->key) {
			compareCount++;
			root = root->left; // 왼쪽 서브트리로 이동
		}
		else {
				compareCount++;
				root = root->right; // 오른쪽 서브트리로 이동
			}
		}
}

// AVL관련
// insert 관련 함수
// 노드 생성 함수
Node* createNode(int key) {
	Node* nptr = (Node*)malloc(sizeof(Node));
	nptr->key = key;
	nptr->right = nptr->left = (Node*)NULL;
	nptr->height = 1;
	return nptr;
}
//높이 반환 함수
int getHeight(Node* nptr) {
	if (nptr == (Node*)NULL) return 0;
	else return nptr->height;
}
//왼쪽 높이-오른쪽 높이
int getBalance(Node* nptr) {
	return getHeight(nptr->left) - getHeight(nptr->right);
}
//오른쪽 회전
Node* rotateRight(Node* y) {
	Node* x = y->left;
	Node* T3 = x->right;

	x->right = y;
	y->left = T3;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
		? getHeight(y->left)
		: getHeight(y->right));

	x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
		? getHeight(x->left)
		: getHeight(x->right));

	return x;
}
//왼쪽회전
Node* rotateLeft(Node* y) {
	Node* x = y->right;
	Node* T2 = x->left;

	x->left = y;
	y->right = T2;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
		? getHeight(y->left)
		: getHeight(y->right));

	x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
		? getHeight(x->left)
		: getHeight(x->right));

	return x;
}
// B를 추가하는 함수
Node* insertNode(Node* root, int key) {
	if (root == (Node*)NULL) return createNode(key);
	if (root->key > key)
		root->left = insertNode(root->left, key);
	else if (root->key < key)
		root->right = insertNode(root->right, key);
	else
		return root;

	root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
		? getHeight(root->left)
		: getHeight(root->right));

	int balance = getBalance(root);

	if (balance >= 2) {
		if (getBalance(root->left) >= 0) return rotateRight(root);
		else /* if (getBalance(root->left) < 0)*/ {
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
		/* else; */
	}
	else if (balance <= -2) {
		if (getBalance(root->right) < 0) return rotateLeft(root);
		else {
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
	}
	else
		return root;
}
//delete 관련 함수
// 트리에서 최소값 노드 찾기
Node* getMinValueNode(Node* node) {
	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}
//삭제를 수행하는 함수
Node* deleteNode(Node* root, int key) {
	// 1. 일반 이진 탐색 트리 삭제
	if (root == NULL) return root;
	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else {
		// 노드 삭제
		if ((root->left == NULL) || (root->right == NULL)) { // 자식 노드가 한개
			Node* temp = root->left ? root->left : root->right; // 그 자식노드를 temp가 가리킴
			if (temp == NULL) { // 자식 노드가 없음
				temp = root; // 메모리 해제할 것
				root = NULL;  // 리턴(되돌려 줄 것)
			}
			else { // 자식 노드가 하나 있음
				*root = *temp; // 하나 있는 자식을 부모로 대치함
			}
			free(temp);
		}
		else {
			// 오른쪽 서브트리에서 최소값 노드 찾기
			Node* temp = getMinValueNode(root->right);
			root->key = temp->key; // 키값만 복사함
			root->right = deleteNode(root->right, temp->key); // 이제 그 최소값을 가진 노드 삭제
		}
	}

	if (root == NULL) return root;

	// 2. 노드 높이 갱신
	root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
		? getHeight(root->left) : getHeight(root->right));

	// 3. 균형 인수 계산
	int balance = getBalance(root);

	// 4. 균형 유지 회전 수행
	// R 회전
	if (balance > 1 && getBalance(root->left) >= 0)
		return rotateRight(root);

	// LR 회전
	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}

	// L 회전
	if (balance < -1 && getBalance(root->right) <= 0)
		return rotateLeft(root);

	// RL 회전
	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	return root;
}
//AVL트리 실행 인터페이스
void doAVLBatch(Node* root) {
	compareCount = 0;
	searchCount = 0;
	for (int i = 0; i <2000; i++) {
		int A = rand() % 3;
		int B = rand() % 1000;
		switch (A) {
		case 0:
			root=insertNode(root, B);
			/*test
			inOrder(root);
			printf("\n");
			*/
			break;
		case 1:
			root=deleteNode(root, B);
			break;
		case 2:
			searchCount++;
			searchNode(root, B);
			break;
		default:
			printf("A 랜덤 지정 오류");
		}
	}
}

//트리 해제
void freeTree(Node* root) {
	if (root == NULL) return; // 기저 조건: NULL이면 종료
	// 왼쪽 서브트리 해제
	freeTree(root->left);
	// 오른쪽 서브트리 해제
	freeTree(root->right);
	// 현재 노드 해제
	free(root);
}

//이진탐색트리
// insert 관련 함수
Node* insert_Node(Node* root, int data) {
	if (root == NULL) return createNode(data);
	if (root->key == data) return root;
	else if (root->key > data)
		root->left = insert_Node(root->left, data);
	else
		root->right = insert_Node(root->right, data);
	return root;
}
//delete 관련 함수
// 트리에서 최소값 노드 찾기
Node* findMin(Node* root) {
	while (root->left != NULL) {
		root = root->left; // 가장 작은 값을 찾기 위해 왼쪽으로 이동
	}
	return root;
}
//삭제 함수
Node* delete_Node(Node* root,int data) {
	if (root == NULL) return root; // 트리가 비어 있으면 반환

	if (data < root->key) {
		root->left = delete_Node(root->left, data); // 왼쪽 서브트리에서 삭제
	}
	else if (data > root->key) {
		root->right = delete_Node(root->right, data); // 오른쪽 서브트리에서 삭제
	}
	else {
		// 삭제할 노드를 찾았을 때
		if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp; // 오른쪽 자식을 반환
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp; // 왼쪽 자식을 반환
		}

		// 두 개의 자식이 있는 경우
		Node* temp = findMin(root->right); // 오른쪽 서브트리에서 가장 작은 값 찾기
		root->key = temp->key; // 데이터를 교체
		root->right = delete_Node(root->right, temp->key); // 오른쪽 서브트리에서 중복 노드 삭제
	}
	return root;
}
//이진탐색트리 실행 인터페이스
void doBinaryBatch(Node* root) {
	compareCount = 0;
	searchCount = 0;
	for (int i = 0; i < 2000; i++) {
		int A = rand() % 3;
		int B = rand() % 1000;
		switch (A) {
		case 0:
			root = insert_Node(root, B);
			/*test
			inOrder(root);
			printf("\n");
			*/
			//B 추가
			break;
		case 1:
			root = delete_Node(root, B);
			break;
		case 2:
			searchCount++;
			searchNode(root, B);//AVL의 탐색과 동일
			break;
		default:
			printf("A 랜덤 지정 오류");
		}
	}
}

//main함수
int main(int argc, char* argv[]) {
	Node* root = NULL;
	srand(time(NULL));
	float allCount = 0.0;
	// 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
	doAVLBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average AVL compare count: %.2f\n", allCount);
	// 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
	freeTree(root);
	root = NULL;
	compareCount = allCount = 0;
	// 과제에서 제시된 Binary Search Tree Batch를 수행한다.
	doBinaryBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average Bin compare count: %.2f\n", allCount);
	freeTree(root);
	return 0;
}