#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100//�迭 �ִ� ũ��
#define INF 1000L//����

struct Edge {			// ������ ��Ÿ���� ����ü
	int start, end, weight;
};

typedef struct GraphType {
	int n;	// ������ ����
	int v; //������ ����
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

//�������� seleted, distance
int selected[MAX_VERTICES];//���ÿ���
int distance[MAX_VERTICES];//���� �Ÿ�

//�׷��� �ʱ�ȭ
void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
	// ���� �� ������Ʈ (start�� end �� �� ū ���� ����)
	if (start > g->v) g->v = start;
	if (end > g->v) g->v = end;
}

// �ּ� dist[v] ���� ���� ������ ��ȯ
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

//Prim�� �̿��� MST�� ã��
void FindPrimMST(GraphType* g)
{
	printf("Prim MST Algorithm\n");//�� �κ� ���
    int i, u, v;
    int start_vertex = 1;  // ���� ���� ����:1

    // ������ �Ÿ�, ���ÿ��� �ʱ�ȭ
    for (u = 0; u <= g->v; u++) {
        distance[u] = INF;
        selected[u] = FALSE;
    }
    distance[start_vertex] = 0;  // ���� ������ �Ÿ��� 0���� ����

    // ������ ����ŭ �ݺ�
    for (i = 0; i <= g->v; i++) {
        u = get_min_vertex(g->v + 1);
        selected[u] = TRUE;

        if (distance[u] == INF) return;  

        printf("���� %d �߰�\n", u);

        // �Ÿ� ������Ʈ
        for (int j = 0; j < g->n; j++) {
            int start = g->edges[j].start;
            int end = g->edges[j].end;
            int weight = g->edges[j].weight;

            // ���õ� �������� �̾����� �������� Ȯ���ϰ�, �Ÿ� ������Ʈ
            if (start == u && !selected[end] && weight < distance[end]) {
                distance[end] = weight;
            } else if (end == u && !selected[start] && weight < distance[start]) {
                distance[start] = weight;
            }
        }
    }
}

//�׷��� ����
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

	//�׷����� �����ϴ� �Լ�
	GenerateGraph(g);

	FindPrimMST(g);//Prim�� �̿��� MST�� ã��

	free(g);
	return 0;
}