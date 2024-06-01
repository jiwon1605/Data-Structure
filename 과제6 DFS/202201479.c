#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100 // 스택의 최대 크기
typedef int element; // 데이터의 자료형
element stack[MAX_STACK_SIZE]; // 1차원 배열
int top = -1;

#define MAX_VERTICES 50
typedef struct GraphType {
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
// 그래프 초기화
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// 공백 상태 검출 함수
int is_empty()
{
	return (top == -1);
}
// 포화 상태 검출 함수
int is_full()
{
	return (top == (MAX_STACK_SIZE - 1));
}
// 삽입 함수
void push(element item)
{
	if (is_full()) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else stack[++top] = item; // why?
}
// 삭제 함수
element pop()
{
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return stack[top--];
}

void dfs_iterative(GraphType* g, int v) {
	int visited[MAX_VERTICES] = { 0 }; // 방문 여부를 저장하는 배열
	push(v);

	while (!is_empty()) {
		v = pop();

		if (!visited[v]) {
			visited[v] = 1;
			printf("정점 -> %d ", v);

			for (int u = g->n - 1; u >= 0; u--) {
				if (g->adj_mat[v][u] && !visited[u]) {
					push(u);
				}
			}
		}
	}

}

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 4; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);
	printf("깊이 우선 탐색\n");
	dfs_iterative(g, 0);
	printf("\n");
	free(g);
	return 0;
}