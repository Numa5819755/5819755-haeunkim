#include <stdlib.h>
#include <stdio.h>

//구조체와 변수
#define MAX_VERTICES 12
typedef int vertex;

typedef struct {
	int n;
	int vertex_list[MAX_VERTICES];
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

typedef struct {
	vertex* data;  // 동적 배열로 스택 데이터 저장
	int top;       // 스택의 최상단 인덱스
	int capacity;  // 스택의 최대 용량
} Stack;

typedef struct {
	vertex* data;  // 동적 배열로 큐 데이터 저장
	int front;     // 큐의 앞쪽 인덱스
	int rear;      // 큐의 뒤쪽 인덱스
	int capacity;  // 큐의 최대 용량
	int size;      // 현재 큐에 있는 원소 수
} Queue;
//그래프
//그래프 초기화 함수
GraphMatType* create_mat_graph() {
	return (GraphMatType*)malloc(sizeof(GraphMatType));
}
//그래프 해제
void destroy_mat_graph(GraphMatType* g) {
	free(g);
}
//그래프 초기화
void init_mat_graph(GraphMatType* g) {
	for (int i = 0; i < MAX_VERTICES; i++)
		g->vertex_list[i] = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++)
			g->adj_mat[i][j] = 0;
}
//그래프 정점 추가
void insert_vertex_mat_graph(GraphMatType* g, int v) {
	if (g->vertex_list[v] == 1) {
		fprintf(stderr, "%d exist already\n", v);
		return;
	}
	if (v > (MAX_VERTICES - 1)) {
		fprintf(stderr, "Over number of vertex\n");
		return;
	}
	g->vertex_list[v] = 1;
}
//간선 추가
void insert_edge_mat_graph(GraphMatType* g, int s, int e) {

	if (g->vertex_list[s] == 0 || g->vertex_list[e] == 0) {
		fprintf(stderr, " edge insert fail: vertex %d or %d dost not exist\n", s, e);
		return;
	}
	g->adj_mat[s][e] = 1;
	g->adj_mat[e][s] = 1;
}

//stack
//스택 초기화
void init_stack(Stack* stack, int capacity) {
	stack->data = (vertex*)malloc(sizeof(vertex) * capacity);  // 초기 크기 할당
	stack->top = -1;  // 스택이 비어있는 상태로 초기화
	stack->capacity = capacity;
}
//스택 비었는지 확인
int is_empty_stack(Stack* stack) {
	return stack->top == -1;  // top이 -1이면 스택이 비어있음
}
//push
void push(Stack* stack, vertex data) {
	if (stack->top == stack->capacity - 1) {
		// 스택이 꽉 찼을 때 크기 늘리기
		stack->capacity *= 2;
		stack->data = (vertex*)realloc(stack->data, sizeof(vertex) * stack->capacity);
	}
	stack->data[++(stack->top)] = data;  // 데이터 삽입
}
//pop
vertex pop(Stack* stack) {
	if (is_empty_stack(stack)) {
		printf("Stack is empty!\n");
		return -1;  // 빈 스택이면 에러 처리
	}
	return stack->data[(stack->top)--];  // 데이터 반환 후 top 감소
}
//queue
//큐 초기화
void init_queue(Queue* queue, int capacity) {
	queue->data = (vertex*)malloc(sizeof(vertex) * capacity);  // 초기 크기 할당
	queue->front = 0;
	queue->rear = -1;
	queue->capacity = capacity;
	queue->size = 0;
}
//큐 비었는지 확인
int is_empty_queue(Queue* queue) {
	return queue->size == 0;  // 큐가 비어있는지 확인
}

void enqueue(Queue* queue, vertex data) {
	if (queue->size == queue->capacity) {
		// 큐가 꽉 찼을 때 크기 늘리기
		queue->capacity *= 2;
		queue->data = (vertex*)realloc(queue->data, sizeof(vertex) * queue->capacity);
	}
	queue->rear = (queue->rear + 1) % queue->capacity;  // 순환 큐 구현
	queue->data[queue->rear] = data;  // 데이터 삽입
	queue->size++;
}

vertex dequeue(Queue* queue) {
	if (is_empty_queue(queue)) {
		printf("Queue is empty!\n");
		return -1;  // 빈 큐이면 에러 처리
	}
	vertex data = queue->data[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;  // 순환 큐
	queue->size--;
	return data;
}
//탐색
//깊이 우선 탐색
void DFS(GraphMatType* g, int start, int target) {
	Stack stack;
	init_stack(&stack, MAX_VERTICES);  // 스택 초기화

	int visited[MAX_VERTICES] = { 0 }; // 방문 기록
	int count = 0;  // 방문한 노드 수
	int found = 0;  // 노드를 찾았는지 여부

	push(&stack, start);  // 시작 노드를 push
	visited[start] = 1;  

	while (!is_empty_stack(&stack)) {
		int current = pop(&stack);
		printf("%d ", current);
		visited[current] = 1;
		count++;

		if (current == target) {
			printf("\n탐색 성공 %d \n", target);
			found = 1; 
			break;
		}

		for (int i = MAX_VERTICES - 1; i >= 0; i--) {
			if (g->adj_mat[current][i] == 1 && !visited[i]) {
				push(&stack, i);
			}
		}
	}

	if (!found) {
		printf("Target %d not found!\n", target);  
	}

	printf("방문한 노드의 수: %d\n\n", count); 
}
//넓이 우선 탐색
void BFS(GraphMatType* g, int start, int target) {
	Queue queue;
	init_queue(&queue, MAX_VERTICES); 
	int visited[MAX_VERTICES] = { 0 };
	int count = 0;  
	int found = 0; 

	enqueue(&queue, start);
	visited[start] = 1; 

	while (!is_empty_queue(&queue)) {
		int current = dequeue(&queue);
		printf("%d ", current);
		count++;

		if (current == target) {
			printf("\n탐색 성공: %d\n", target);
			found = 1;
			break;
		}

		for (int i = 0; i < MAX_VERTICES; i++) {
			if (g->adj_mat[current][i] == 1 && !visited[i]) {
				enqueue(&queue, i);
				visited[i] = 1;  
			}
		}
	}

	if (!found) {
		printf("Target %d not found!\n", target);
	}
	printf("방문한 노드의 수: %d\n\n", count);
}

//User Interface
//메뉴
void menu() {
	printf("-------------------\n");
	printf("1 : 깊이 우선 탐색 |\n");
	printf("2 : 너비 우선 탐색 |\n");
	printf("3 : 종료           |\n");
	printf("-------------------\n");
	printf("\n");
}
//사용자 입력
void User_Interface(GraphMatType* g) {
	menu();
	int num, start, search;
	num = start = search = 0;
	while (1) {
		printf("메뉴 입력: ");
		scanf_s("%d", &num);
		switch (num) {
		case 1:
			printf("시작 번호와 탐색할 값 입력: ");
			scanf_s("%d %d", &start, &search);
			DFS(g, start, search);
			break;
		case 2:
			printf("시작 번호와 탐색할 값 입력: ");
			scanf_s("%d %d", &start, &search);
			BFS(g, start, search);
			break;
		case 3:
			return;
			break;
		default:
			printf("다시 입력하세요.\n");
		}
	}
}
main() {

	GraphMatType* g;

	g = create_mat_graph();
	init_mat_graph(g);

	insert_vertex_mat_graph(g, 0);
	insert_vertex_mat_graph(g, 1);
	insert_vertex_mat_graph(g, 2);
	insert_vertex_mat_graph(g, 3);
	insert_vertex_mat_graph(g, 4);
	insert_vertex_mat_graph(g, 5);
	insert_vertex_mat_graph(g, 6);
	insert_vertex_mat_graph(g, 7);
	insert_vertex_mat_graph(g, 8);
	insert_vertex_mat_graph(g, 9);
	insert_vertex_mat_graph(g, 10);

	insert_edge_mat_graph(g, 0, 2);
	insert_edge_mat_graph(g, 0, 4);
	insert_edge_mat_graph(g, 0, 5);
	insert_edge_mat_graph(g, 0, 6);
	insert_edge_mat_graph(g, 0, 9);
	insert_edge_mat_graph(g, 2, 3);
	insert_edge_mat_graph(g, 2, 4);
	insert_edge_mat_graph(g, 4, 1);
	insert_edge_mat_graph(g, 4, 3);
	insert_edge_mat_graph(g, 4, 5);
	insert_edge_mat_graph(g, 4, 6);
	insert_edge_mat_graph(g, 4, 7);
	insert_edge_mat_graph(g, 5, 3);
	insert_edge_mat_graph(g, 5, 1);
	insert_edge_mat_graph(g, 6, 7);
	insert_edge_mat_graph(g, 6, 8);
	insert_edge_mat_graph(g, 9, 8);
	insert_edge_mat_graph(g, 1, 7);
	insert_edge_mat_graph(g, 1, 10);
	insert_edge_mat_graph(g, 7, 10);
	insert_edge_mat_graph(g, 8, 10);

	User_Interface(g);

	destroy_mat_graph(g);

}