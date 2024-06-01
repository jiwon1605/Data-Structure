#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100 // ������ �ִ� ũ��
typedef int element; // �������� �ڷ���
element stack[MAX_STACK_SIZE]; // 1���� �迭
int top = -1;

#define MAX_VERTICES 50
typedef struct GraphType {
	int n; // ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
// �׷��� �ʱ�ȭ
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// ���� ���� ���� �Լ�
int is_empty()
{
	return (top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full()
{
	return (top == (MAX_STACK_SIZE - 1));
}
// ���� �Լ�
void push(element item)
{
	if (is_full()) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else stack[++top] = item; // why?
}
// ���� �Լ�
element pop()
{
	if (is_empty()) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return stack[top--];
}

void dfs_iterative(GraphType* g, int v) {
	int visited[MAX_VERTICES] = { 0 }; // �湮 ���θ� �����ϴ� �迭
	push(v);

	while (!is_empty()) {
		v = pop();

		if (!visited[v]) {
			visited[v] = 1;
			printf("���� -> %d ", v);

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
	printf("���� �켱 Ž��\n");
	dfs_iterative(g, 0);
	printf("\n");
	free(g);
	return 0;
}