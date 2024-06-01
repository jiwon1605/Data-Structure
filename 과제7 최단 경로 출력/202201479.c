#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */
typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int path[MAX_VERTICES]; //경유 노드 저장
int distance[MAX_VERTICES]; /* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES]; /* 방문한 정점 표시 */
//distance배열에서 최소값 찾고, 그 인덱스 반환
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		//현재까지의 최소값보다 작은 값을 찾는 if 문
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos; //최솟값의 인덱스 반환
}
void print_status(GraphType* g)
{
	static int step = 1; // static ? 외부에서도 사용가능
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
		printf("%2d ", found[i]); //found의 요소 출력
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
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i]; //초기값은 시작 정점에서의 가중치 값
		found[i] = FALSE; //초기에는 모든 정점이 방문 안했으므로 false
		path[i] = start;
	}
	found[start] = TRUE; /* 시작 정점 방문 표시 */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		print_status(g); //각 단계의 상태 출력
		u = choose(distance, g->n, found); //최소값 찾고 해당 정점 선택
		found[u] = TRUE; //방문함을 표기
		for (w = 0; w < g->n; w++)
			if (!found[w]) //선택된 정점과 연결된 정점들에 대해 거리 값 업데이트
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];//거리 값 업데이트
					path[w] = u;
				}//선택된 정점을 거쳐 해당 정점으로 가는 거리가 더 짧은 경우
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
