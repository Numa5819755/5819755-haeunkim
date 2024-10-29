#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];		// 부모 노드
// 초기화
void set_init(int n)
{
	for (int i = 1; i <= n; i++)
		parent[i] = -1;
}
// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 			// 루트 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}
// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// 노드 a의 루트를 찾는다. 
	int root2 = set_find(b);	// 노드 b의 루트를 찾는다. 
	if (root1 != root2) 	// 합한다. 
		parent[root1] = root2;
}

struct Edge {			// 간선을 나타내는 구조체
	int start, end, weight;
};

typedef struct GraphType {
	int n;	// 간선의 개수
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}
// qsort()에 사용되는 함수
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}
// 그래프에서 최대 정점을 찾아 정점 수 추정
int find_vertex_count(GraphType* g) {
	int max_vertex = 0;
	for (int i = 0; i < g->n; i++) {
		if (g->edges[i].start > max_vertex) {
			max_vertex = g->edges[i].start;
		}
		if (g->edges[i].end > max_vertex) {
			max_vertex = g->edges[i].end;
		}
	}
	return max_vertex;
}
// kruskal의 최소 비용 신장 트리 프로그램
void QuickKruskal(GraphType* g)
{
	GraphType* c = g;
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수	
	int uset, vset;			// 정점 u와 정점 v의 집합 번호
	struct Edge e;

	int vertex_count = find_vertex_count(g);
	set_init(c->n);				// 집합 초기화
	qsort(c->edges, c->n, sizeof(struct Edge), compare);

	printf("Quick Based Kruskal \n");
	int i = 0;
	while (edge_accepted < (vertex_count - 1) && i < g->n)	// 간선의 수 < (n-1)
	{
		e = c->edges[i];
		uset = set_find(e.start);		// 정점 u의 집합 번호 
		vset = set_find(e.end);		// 정점 v의 집합 번호
		if (uset != vset) {			// 서로 속한 집합이 다르면
			printf("Edge (%d,%d) select %d \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
		}
		i++;
	}
	printf("\n");
}

//그래프 생성
void GenerateGraph(GraphType* g) {
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 9, 10, 10);
}
//minheap을 위한 함수
//구조체 선언
typedef struct {
	struct Edge* edges;   
	int size;          
} MinHeap;

// minheap초기화
void min_heap_init(MinHeap* heap, int capacity) {
	heap->edges = (struct Edge*)malloc(sizeof(struct Edge) * capacity);
	heap->size = 0;
}

// heap 속성 유지->배열 재정렬
void min_heapify(MinHeap* heap, int i) {
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < heap->size && heap->edges[left].weight < heap->edges[smallest].weight)
		smallest = left;
	if (right < heap->size && heap->edges[right].weight < heap->edges[smallest].weight)
		smallest = right;
	if (smallest != i) {
		struct Edge temp = heap->edges[i];
		heap->edges[i] = heap->edges[smallest];
		heap->edges[smallest] = temp;
		min_heapify(heap, smallest);
	}
}

// minheap에 edge 삽입
void min_heap_insert(MinHeap* heap, struct Edge edge) {
	int i = heap->size++;
	heap->edges[i] = edge;
	while (i != 0 && heap->edges[(i - 1) / 2].weight > heap->edges[i].weight) {
		struct Edge temp = heap->edges[i];
		heap->edges[i] = heap->edges[(i - 1) / 2];
		heap->edges[(i - 1) / 2] = temp;
		i = (i - 1) / 2;
	}
}

// 힙의 루트 간선 반환: 최소 가중치 간선 
struct Edge min_heap_extract_min(MinHeap* heap) {
	struct Edge root = heap->edges[0];
	heap->edges[0] = heap->edges[--heap->size];
	min_heapify(heap, 0);
	return root;
}

// MinHeapKruskal 함수
void MinHeapKrusKal(GraphType* g) {

	MinHeap heap;
	min_heap_init(&heap, g->n);

	for (int i = 0; i < g->n; i++) {
		min_heap_insert(&heap, g->edges[i]);

	}

	int edge_accepted = 0;
	set_init(g->n);

	printf("MinHeap Based Kruskal\n");

	while (edge_accepted < (g->n - 1) && heap.size > 0) {
		struct Edge e = min_heap_extract_min(&heap);
		int uset = set_find(e.start);
		int vset = set_find(e.end);
		if (uset != vset) {
			printf("Edge (%d,%d) selected %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
	}

	free(heap.edges);
}

//main함수
int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));

	graph_init(g);
	//그래프를 생성하는 함수
	GenerateGraph(g);

	QuickKruskal(g);
	MinHeapKrusKal(g);
	free(g);
	return 0;
}

