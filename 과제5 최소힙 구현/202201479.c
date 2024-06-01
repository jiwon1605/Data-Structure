#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENT 200
typedef struct element{
	int key;
	struct element* left;
	struct element* right;
} element;

typedef struct{
	element* heap;
	int heap_size;
} HeapType;

// 생성 함수
HeapType* create_heap(){
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	h->heap = (element*)malloc(sizeof(element) * MAX_ELEMENT);
	for (int i = 0; i < MAX_ELEMENT; i++) {
		h->heap[i].left = h->heap[i].right = NULL;
	}
	return h;
}

// 초기화 함수
void init(HeapType* h)
{
	h-> heap_size = 0;
}

//노드 동적 생성
element* new_element(element item) {
	element* temp = (element*)malloc(sizeof(element));
	temp->key = item.key;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

//최소 힙이 비어있는지 검사
int is_empty(HeapType*h) {
	return(h->heap_size == 0);
}

// 삽입 함수
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);
	if (h == NULL)
		h->heap[i] = *new_element(item);
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i].key = item.key; // 새로운 노드를 삽입
}

// 삭제 함수
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	if (is_empty(h))
		return h->heap[1];
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

int main(void) {
	element e1={30},e2={50},e3={10},e4={20}, e5={5};
	element e6,e7,e8,e9,e10;
	HeapType* heap;
	heap = create_heap(); // 히프 생성
	init(heap); // 초기화
	// 삽입
	insert_min_heap(heap,e1);
	insert_min_heap(heap,e2);
	insert_min_heap(heap,e3);
	insert_min_heap(heap,e4);
	insert_min_heap(heap,e5);
	// 삭제
	e6 = delete_min_heap(heap);
	printf("<%d>\n",e6.key);
	e7 = delete_min_heap(heap);
	printf("<%d>\n", e7.key);
	e8 = delete_min_heap(heap);
	printf("<%d>\n", e8.key);
	e9 = delete_min_heap(heap);
	printf("<%d>\n", e9.key);
	e10 = delete_min_heap(heap);
	printf("<%d>\n", e10.key);
	free(heap);
	return 0;
}