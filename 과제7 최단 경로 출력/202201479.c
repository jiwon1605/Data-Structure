#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* ���Ѵ� (������ ���� ���) */
typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int path[MAX_VERTICES]; //���� ��� ����
int distance[MAX_VERTICES]; /* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES]; /* �湮�� ���� ǥ�� */
//distance�迭���� �ּҰ� ã��, �� �ε��� ��ȯ
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		//��������� �ּҰ����� ���� ���� ã�� if ��
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos; //�ּڰ��� �ε��� ��ȯ
}
void print_status(GraphType* g)
{
	static int step = 1; // static ? �ܺο����� ��밡��
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++)
	{
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]); //found�� ��� ���
	printf("\n\n");
}

void print_path(int start, int end) {
	int e = end;
	int s = start;
	if (start != end) {
		print_path(start, path[e]);
		printf("<%d->%d>", path[e], e);
	}

}

void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
	{
		distance[i] = g->weight[start][i]; //�ʱⰪ�� ���� ���������� ����ġ ��
		found[i] = FALSE; //�ʱ⿡�� ��� ������ �湮 �������Ƿ� false
		path[i] = start;
	}
	found[start] = TRUE; /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		print_status(g); //�� �ܰ��� ���� ���
		u = choose(distance, g->n, found); //�ּҰ� ã�� �ش� ���� ����
		found[u] = TRUE; //�湮���� ǥ��
		for (w = 0; w < g->n; w++)
			if (!found[w]) //���õ� ������ ����� �����鿡 ���� �Ÿ� �� ������Ʈ
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];//�Ÿ� �� ������Ʈ
					path[w] = u;
				}//���õ� ������ ���� �ش� �������� ���� �Ÿ��� �� ª�� ���
	}
}

int main(void)
{
	GraphType g = { 7,
	{{ 0, 7, INF, INF, 3, 10, INF },
	{ 7, 0, 4, 10, 2, 6, INF },
	{ INF, 4, 0, 2, INF, INF, INF },
	{ INF, 10, 2, 0, 11, 9, 4 },
	{ 3, 2, INF, 11, 0, INF, 5 },
	{ 10, 6, INF, 9, INF, 0, INF },
	{ INF, INF, INF, 4, 5, INF, 0 } }
	};
	shortest_path(&g, 0);
	print_path(0, 3);
	return 0;
}
