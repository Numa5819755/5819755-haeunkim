#include <stdio.h>
#include <stdlib.h>
//구조체,변수정의(리스트)
typedef struct {
	int number;
	int weight;//가중치
} element;

typedef struct DListNode {	// 이중 연결 노드 타입
	element vertex;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

//구조체,변수정의(그래프)
#define MAX_VERTICES 100

typedef struct {
	int num_of_vertex;
	int num_of_edge;
	DListNode adj_list[MAX_VERTICES];
}GraphListType;

//구조체,변수정의(힙)
#define MAX_ELEMENT 100

typedef struct {
	int key;
	int start, end;
} heap_element;

typedef struct {
	heap_element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

//구조체, 변수정의(Dijkstra heap x)
#define TRUE 1
#define FALSE 0
#define INF	1000000	//무한대 (연결이 없는 경우) 

//list
void init_Dlist(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

void print_Dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {//돌고 돌아 다시 head에 가면 반복 종료
		printf(" |%d(%d)| ", p->vertex.number, p->vertex.weight);
	}
	printf("\n");
}

void insert_Dlist(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->vertex.number = data.number; // vertex
	newnode->vertex.weight = data.weight;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// 노드 removed를 삭제한다.
void delete_Dlist(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

DListNode* search_Dlist(DListNode* head, element data) {

	DListNode* node = head->rlink;
	do {
		if (node->vertex.number == data.number) return node;
		else node = node->rlink;
	} while (node != head);
	return (DListNode*)NULL;
}
//그래프
GraphListType* create_list_graph() {
	return (GraphListType*)malloc(sizeof(GraphListType));
}

void destroy_list_graph(GraphListType* g) {//이중연결리스트 루트에 연결되어 있는 노드를 모두 free한 후 루트노드 free
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (g->adj_list[i].vertex.number != -1) {//초반에 -1로 배열을 초기화
			DListNode* head, * next;
			head = &(g->adj_list[i]);
			next = head->rlink;
			while (head != next) {//head와 next가 같지 않을 때까지 반복
				delete_Dlist(head, next);
				next = head->rlink;
			}
		}
		g->adj_list[i].vertex.number = -1;
	}
	free(g);
}

void init_list_graph(GraphListType* g) {

	for (int i = 0; i < MAX_VERTICES; i++) {
		init_Dlist(&(g->adj_list[i]));
		g->adj_list[i].vertex.number = -1;
	}
	g->num_of_edge = g->num_of_vertex = 0;//변수 초기화
}

void insert_vertex_list_graph(GraphListType* g, int v) {
	if (g->adj_list[v].vertex.number == -1) {
		g->adj_list[v].vertex.number = v;
		(g->num_of_vertex)++;
	}
	else {
		printf("vertex %d already exist in graph\n", v);
	}
}

void insert_edge_list_graph(GraphListType* g, int s, int e, int w) {
	if (search_Dlist(&(g->adj_list[s]), (element) { e, w }) == NULL) {
		insert_Dlist(&(g->adj_list[s]), (element) { e, w });
		insert_Dlist(&(g->adj_list[e]), (element) { s, w });
		(g->num_of_edge)++;
	}
	else {
		printf("edge (%d,%d) already exist in graph\n", s, e);
	}
}

void delete_vertex_list_graph(GraphListType* g, int v) {
	if (g->adj_list[v].rlink != &(g->adj_list[v])) {
		printf(" vertex delete fail: %d has edge\n", v);
		return;
	}
	g->adj_list[v].vertex.number = -1;
	(g->num_of_vertex)--;
}

void delete_edge_list_graph(GraphListType* g, int s, int e) {
	DListNode* v, * w;

	v = search_Dlist(&(g->adj_list[s]), (element) { e, 0 });
	w = search_Dlist(&(g->adj_list[e]), (element) { s, 0 });
	if (v != NULL && w != NULL) {
		delete_Dlist(&(g->adj_list[s]), v);
		delete_Dlist(&(g->adj_list[e]), w);
		(g->num_of_edge)--;
	}
	else {
		printf("Delete edge: edge (%d,%d) does not exist in graph\n", s, e);
	}
}

int is_vertex_in_graph(GraphListType* g, int v) {
	return (g->adj_list[v].vertex.number == v);
}

void print_adj_list(GraphListType* g) {
	printf("\n인접리스트 출력\n");
	for (int i = 0; i <= MAX_VERTICES; i++) {//MAC_VERTICES => g->num_of_vertex
		if (g->adj_list[i].vertex.number >= 0) {
			printf(" Vertex %d ", i);
			print_Dlist(&(g->adj_list[i]));
		}
	}
}
//heapX Dijkstra
//중간상태 출력
void print_status(int distance[], int found[], int n) {
	printf("Distance: ");
	for (int i = 1; i <= n; i++) {
		if (distance[i] == INF) {
			printf("* ");
		}
		else {
			printf("%d ", distance[i]);
		}
	}
	printf("\nFound: ");
	for (int i = 1; i <= n; i++) {
		printf("%d ", found[i]);
	}
	printf("\n\n");
}
//최소가중치 정점 선택
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 1; i <= n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
void Dijkstra(GraphListType* g, int start)
{
	int distance[MAX_VERTICES];
	int found[MAX_VERTICES];
	int found_order[MAX_VERTICES];
	int i, u;
	int order_index = 0;

	// 초기화
	for (i = 1; i <= g->num_of_vertex; i++) {
		distance[i] = INF;
		found[i] = FALSE;
	}
	distance[start] = 0;

	for (i = 1; i <= g->num_of_vertex ; i++) {
		u = choose(distance, g->num_of_vertex, found);
		if (u == -1) break;
		found[u] = TRUE;
		found_order[order_index++] = u;

		print_status(distance, found, g->num_of_vertex);

		DListNode* current = g->adj_list[u].rlink;
		while (current != &(g->adj_list[u])) {
			int v = current->vertex.number;
			int weight = current->vertex.weight;
			if (!found[v] && distance[u] + weight < distance[v]) {
				distance[v] = distance[u] + weight;
			}
			current = current->rlink;
		}
	}

	// Found Order 출력
	printf("Found Order: ");
	for (i = 0; i < order_index; i++) {
		printf("%d ", found_order[i]);
	}
	printf("\n");
}
//heap 
HeapType* create_heap() {
	return (HeapType*)malloc(sizeof(HeapType));
}
void init_heap(HeapType* h) {
	h->heap_size = 0;
}
void destroy_heap(HeapType* h) {
	free(h);
}

void insert_min_heap(HeapType* h, heap_element item) {

	int i = h->heap_size + 1;

	while ((i > 1) && h->heap[i / 2].key > item.key) {
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
	(h->heap_size)++;
}

heap_element delete_min_heap(HeapType* h) {
	int parent, child;
	heap_element item, temp;

	//if (h->heap_size < 1) return ((heap_element) NULL);

	item = h->heap[1];
	temp = h->heap[h->heap_size];
	(h->heap_size)--;

	for (parent = 1, child = 2; child <= h->heap_size; parent = child, child *= 2) {
		if ((child < h->heap_size) &&
			(h->heap[child].key > h->heap[child + 1].key)) child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
	}

	h->heap[parent] = temp;
	return item;
}

//heapO Dijkstra_보너스
void Dijkstra_heap(GraphListType* g, int start) {
	int dist[MAX_VERTICES], prev[MAX_VERTICES], found[MAX_VERTICES];
	HeapType* h;
	DListNode* nptr;
	int found_order[MAX_VERTICES];
	int order_index = 0;

	h = create_heap();
	init_heap(h);

	for (int i = 0; i <= g->num_of_vertex; i++) {
		dist[i] = INF;
		found[i] = FALSE;
		prev[i] = -1;
	}
	dist[start] = 0;
	insert_min_heap(h, (heap_element) { 0, start, start }); // 시작 정점을 힙에 추가

	while (h->heap_size > 0) {
		heap_element min_edge = delete_min_heap(h);
		int u = min_edge.end;

		if (found[u]) continue; // 이미 방문한 정점이면 무시
		found[u] = TRUE;
		found_order[order_index++] = u; // 방문 순서 기록
		prev[u] = min_edge.start;

		// 중간 상태 출력
		print_status(dist, found, g->num_of_vertex);

		// 인접 정점 업데이트
		nptr = g->adj_list[u].rlink;
		while (nptr != &(g->adj_list[u])) {
			int v = nptr->vertex.number;
			int weight = nptr->vertex.weight;

			if (!found[v] && dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
				insert_min_heap(h, (heap_element) { dist[v], u, v });
			}
			nptr = nptr->rlink;
		}
	}

	// Found Order 출력
	printf("Found Order: ");
	for (int i = 0; i < order_index; i++) {
		printf("%d ", found_order[i]);
	}
	printf("\n");
}

//그래프 생성
void GenerateGraph(GraphListType* h) {

	insert_vertex_list_graph(h, 1);
	insert_vertex_list_graph(h, 2);
	insert_vertex_list_graph(h, 3);
	insert_vertex_list_graph(h, 4);
	insert_vertex_list_graph(h, 5);
	insert_vertex_list_graph(h, 6);
	insert_vertex_list_graph(h, 7);
	insert_vertex_list_graph(h, 8);
	insert_vertex_list_graph(h, 9);
	insert_vertex_list_graph(h, 10);

	insert_edge_list_graph(h, 1, 2, 3);
	insert_edge_list_graph(h, 1, 6, 11);
	insert_edge_list_graph(h, 1, 7, 12);
	insert_edge_list_graph(h, 2, 3, 5);
	insert_edge_list_graph(h, 2, 4, 4);
	insert_edge_list_graph(h, 2, 5, 1);
	insert_edge_list_graph(h, 2, 6, 7);
	insert_edge_list_graph(h, 2, 7, 8);
	insert_edge_list_graph(h, 3, 4, 2);
	insert_edge_list_graph(h, 3, 7, 6);
	insert_edge_list_graph(h, 3, 8, 5);
	insert_edge_list_graph(h, 4, 5, 13);
	insert_edge_list_graph(h, 4, 8, 14);
	insert_edge_list_graph(h, 4, 10, 27);
	insert_edge_list_graph(h, 5, 6, 9);
	insert_edge_list_graph(h, 5, 9, 18);
	insert_edge_list_graph(h, 5, 10, 17);
	insert_edge_list_graph(h, 7, 8, 13);
	insert_edge_list_graph(h, 8, 10, 15);
	insert_edge_list_graph(h, 9, 10, 10);
}
//메인
int main() {
	GraphListType* h;
	h = create_list_graph();
	init_list_graph(h);
	//그래프 생성
	GenerateGraph(h);
	printf("[heap X, Dijkstra]\n\n");
	Dijkstra(h, 1);
	printf("\n[heap O, Dijkstra]\n\n");
	Dijkstra_heap(h, 1);
	destroy_list_graph(h);
	return 0;
}