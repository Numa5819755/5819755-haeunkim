#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

// element 구조체 정의
typedef struct {
	int key;
} element;

// TreeNode 구조체 정의
typedef struct {
	element heap[MAX_SIZE]; // 힙
	int heap_size;          // 현재 힙의 크기
} TreeNode;

// 트리 초기화
TreeNode* create_init() {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->heap_size = 0; // 힙 크기 초기화
	return temp;
}

// 트리에 데이터를 삽입하는 함수
void InsertMaxHeapTree(TreeNode* root, int data) {
	element item;
	item.key = data; // 삽입할 데이터
	int i = ++(root->heap_size); // 힙 크기 증가 후 i에 대입
	while ((i != 1) && (item.key > root->heap[i / 2].key)) { // 부모 노드와 비교
		root->heap[i] = root->heap[i / 2]; // 부모 노드를 아래로 이동
		i = i / 2; // 부모로 이동
	}
	root->heap[i] = item; //해당 위치에 삽입
}

// inputdata 배열의 데이터로 힙 트리 생성
TreeNode* generateMaxHeapTree(int inputData[], int size) {
	TreeNode* root = create_init(); // 초기화
	for (int i = 0; i < size; i++) {
		InsertMaxHeapTree(root, inputData[i]); // 데이터 삽입
	}
	return root;
}

// 사용자 인터페이스 메뉴 출력
void menu() {
	printf("---------------\n");
	printf("|i:노드 추가  |\n");
	printf("|d:노드 삭제  |\n");
	printf("|p:레벨별 출력|\n");
	printf("|c:종료       |\n");
	printf("---------------\n");
}

// 레벨 순서대로 출력
void level_print(TreeNode* root) {
	for (int i = 1; i <= root->heap_size; i++) {
		printf("%d ", root->heap[i].key); // 노드의 key 값을 출력
	}
	printf("\n");
}

// 사용자 인터페이스 노드 삽입하는 함수
void insert_node(TreeNode* root) {
	int insert_data;
	int count = 0;
	printf("추가할 값 입력: ");
	scanf_s("%d", &insert_data); // 삽입할 데이터 입력 받기

	int i = ++(root->heap_size); // 힙 크기 증가 후 i에 대입
	root->heap[i].key = insert_data; // 새로운 노드를 마지막 위치에 추가

	level_print(root); // 초기 상태 출력

	// upheap 과정
	while ((i > 1) && (root->heap[i / 2].key < insert_data)) {
		root->heap[i].key = root->heap[i / 2].key; // 부모 노드를 아래로 이동
		i = i / 2; // 부모로 이동
		root->heap[i].key = insert_data; // 해당 위치에 삽입
		level_print(root); // 중간 상태 출력
		count++; // 이동 횟수 추가
	}

	printf("노드가 이동된 횟수: %d\n", count); // 이동된 횟수 출력
}

// 사용자 인터페이스 노드를 삭제하는 함수
void delete_node(TreeNode* root) {
	if (root->heap_size == 0) {
		return; // 힙이 비어 있으면 종료
	}

	int parent = 1;
	int child = 2;
	int count = 0;
	element item = root->heap[1]; // 삭제할 루트 노드
	element temp = root->heap[(root->heap_size)--];  // 마지막 노드 저장 후 힙 사이즈 감소

	root->heap[parent] = temp;  // 루트에 마지막 노드 배치
	count++; // 이동 횟수 추가

	level_print(root); // 초기 상태 출력

	// downheap 과정
	while (child <= root->heap_size) {
		if (child < root->heap_size && root->heap[child].key < root->heap[child + 1].key) {
			child++; // 자식 중 더 큰 자식 선택
		}
		if (temp.key >= root->heap[child].key) break; // 조건 만족-> 종료

		root->heap[parent] = root->heap[child]; // 자식을 부모로 이동
		count++; // 이동 횟수 추가
		parent = child; // 자식 위치로 이동
		child *= 2; // 자식 노드 계산
		root->heap[parent] = temp; // 노드를 적절한 위치에 배치
		level_print(root); // 중간 상태 출력
	}
	printf("노드가 이동된 횟수: %d\n", count); // 이동된 횟수 출력
}

// 힙을 레벨별로 출력
void print_node(TreeNode* root) {
	int level = 1; // 레벨 번호
	int index = 1; // 현재 노드 인덱스
	int nodes_at_level = 1; // 현재 레벨에 있는 노드 수

	while (index <= root->heap_size) {
		printf("[%d] ", level); // 레벨 번호 출력
		for (int i = 0; i < nodes_at_level && index <= root->heap_size; i++) {
			printf("%d ", root->heap[index].key); // 해당 레벨의 노드 출력
			index++;
		}
		printf("\n");
		level++; // 다음 레벨로 이동
		nodes_at_level *= 2; // 다음 레벨의 노드 수는 2배
	}
}

// 사용자 인터페이스 실행 함수
void runUserInterface(TreeNode* root) {
	menu(); // 메뉴 출력
	char ch;
	for (;;) {
		printf("메뉴 입력: ");
		scanf_s(" %c", &ch); // 메뉴 선택 입력
		if (ch == 'c') // 'c'를 입력하면 종료
			break;
		switch (ch) {
		case 'i': insert_node(root); printf("\n"); break; // 노드 삽입
		case 'd': delete_node(root);  printf("\n"); break; // 노드 삭제
		case 'p': print_node(root);  printf("\n"); break; // 레벨별 출력
		default: printf("다시 입력하세요."); // 잘못된 입력 처리
		}
	}
}

// 메인 함수
int main() {
	int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 5 }; // 초기 데이터
	int size = 10;
	TreeNode* root = generateMaxHeapTree(inputData, size); // 최대 힙 트리 생성
	runUserInterface(root); // 사용자 인터페이스
	free(root); 
	return 0;
}
