#include <stdio.h>
#include <stdlib.h>
// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct { // 큐 타입
	element* data;
	int front, rear;
	int count;
	int capacity ;
} QueueType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화 함수
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
	q->count = 0;
	q->capacity = MAX_QUEUE_SIZE;
	q->data = (element*)malloc(sizeof(element) * MAX_QUEUE_SIZE);
}
// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->count == 0);

}
// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return (q->count == q->capacity-1);
}
// 원형큐 출력 함수
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

//resize 함수
void resize(QueueType* q)
{
	//capacity를 두배로 해주고
	q->capacity *= 2;
	//realloc
	q->data = (element*)realloc(q->data, q->capacity * sizeof(element));
	

}

// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q)) {
		resize(q);
	}
	q->data[q->rear] = item;
	q->rear = (q->rear+1) % q->capacity;
	q->count++;
}

// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");

	q->front = (q->front+1) % q->capacity;
	q->count--;
	return q->data[q->front];
}

int main(void) {
	QueueType queue;
	int element;
	init_queue(&queue);
	printf("--데이터 추가 단계--\n");

	for (int i = 0; i < 100; i++) {
		element = i + 1;
		enqueue(&queue, element);
		queue_print(&queue);
	}
	
	/*printf("큐는 포화상태입니다.\n\n");
	printf("--데이터 삭제 단계--\n");
	while (!is_empty(&queue)) {
		element = dequeue(&queue);
		printf("꺼내진 정수: %d\n", element);
		queue_print(&queue);
	}
	printf("큐는 공백상태입니다.\n");*/
	return 0;
}