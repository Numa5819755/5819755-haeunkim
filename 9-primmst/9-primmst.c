#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100//배열 최대 크기
#define INF 1000L//무한

struct Edge {			// 간선을 나타내는 구조체
	int start, end, weight;
};

typedef struct GraphType {
	int n;	// 간선의 개수
	int v; //정점의 개수
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

//전역변수 seleted, distance
int selected[MAX_VERTICES];//선택여부
int distance[MAX_VERTICES];//엣지 거리

//그래프 초기화
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
	// 정점 수 업데이트 (start와 end 중 더 큰 값을 선택)
	if (start > g->v) g->v = start;
	if (end > g->v) g->v = end;
}

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	return (v);
}

//Prim을 이용해 MST를 찾음
void FindPrimMST(GraphType* g)
{
	printf("Prim MST Algorithm\n");//윗 부분 출력
    int i, u, v;
    int start_vertex = 1;  // 시작 정점 설정:1

    // 정점의 거리, 선택여부 초기화
    for (u = 0; u <= g->v; u++) {
        distance[u] = INF;
        selected[u] = FALSE;
    }
    distance[start_vertex] = 0;  // 시작 정점의 거리만 0으로 설정

    // 정점의 수만큼 반복
    for (i = 0; i <= g->v; i++) {
        u = get_min_vertex(g->v + 1);
        selected[u] = TRUE;

        if (distance[u] == INF) return;  

        printf("정점 %d 추가\n", u);

        // 거리 업데이트
        for (int j = 0; j < g->n; j++) {
            int start = g->edges[j].start;
            int end = g->edges[j].end;
            int weight = g->edges[j].weight;

            // 선택된 정점에서 이어지는 간선인지 확인하고, 거리 업데이트
            if (start == u && !selected[end] && weight < distance[end]) {
                distance[end] = weight;
            } else if (end == u && !selected[start] && weight < distance[start]) {
                distance[start] = weight;
            }
        }
    }
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
int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	//그래프를 생성하는 함수
	GenerateGraph(g);

	FindPrimMST(g);//Prim을 이용해 MST를 찾음

	free(g);
	return 0;
}