#include <stdio.h>
#include <stdlib.h>
// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct { // ť Ÿ��
	element* data;
	int front, rear;
	int count;
	int capacity ;
} QueueType;
// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// �ʱ�ȭ �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
	q->count = 0;
	q->capacity = MAX_QUEUE_SIZE;
	q->data = (element*)malloc(sizeof(element) * MAX_QUEUE_SIZE);
}
// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->count == 0);

}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return (q->count == q->capacity-1);
}
// ����ť ��� �Լ�
void queue_print(QueueType* q)
{
	
	printf("QUEUE(front=%d rear=%d count=%d) = ", q->front, q->rear, q->count);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i) % (q->capacity);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
			i++;
			
		} while (i < q->count);
	}
	printf("\n");
}

//resize �Լ�
void resize(QueueType* q)
{
	//capacity�� �ι�� ���ְ�
	q->capacity *= 2;
	//realloc
	q->data = (element*)realloc(q->data, q->capacity * sizeof(element));
	

}

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q)) {
		resize(q);
	}
	q->data[q->rear] = item;
	q->rear = (q->rear+1) % q->capacity;
	q->count++;
}

// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");

	q->front = (q->front+1) % q->capacity;
	q->count--;
	return q->data[q->front];
}

int main(void) {
	QueueType queue;
	int element;
	init_queue(&queue);
	printf("--������ �߰� �ܰ�--\n");

	for (int i = 0; i < 100; i++) {
		element = i + 1;
		enqueue(&queue, element);
		queue_print(&queue);
	}
	
	/*printf("ť�� ��ȭ�����Դϴ�.\n\n");
	printf("--������ ���� �ܰ�--\n");
	while (!is_empty(&queue)) {
		element = dequeue(&queue);
		printf("������ ����: %d\n", element);
		queue_print(&queue);
	}
	printf("ť�� ��������Դϴ�.\n");*/
	return 0;
}