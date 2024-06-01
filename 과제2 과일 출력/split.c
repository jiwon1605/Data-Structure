#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[100];
}element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	if (!p) error("메모리 할당 에러");
	p->data = value;
	p->link = head;
	head = p;
	return p;
}
void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%s->", p->data.name);
	printf("NULL\n");
}



ListNode* search_list(ListNode* head, element value) {
	ListNode* p = head;

	while (p != NULL) {
		if (strcmp(p->data.name, value.name) == 0) return p;
		p = p->link;
	}
	return NULL;
}

ListNode* delete(ListNode* head, element value) {
	if (head == NULL) {
		fprintf(stderr, "공백 오류");
		exit(1);
	}
	else {
		ListNode* p = head;
		ListNode* prev = NULL;
		ListNode* remove = search_list(head, value);

		while (p != remove) {
			prev = p;
			p = p->link;
		}
		if (prev == NULL) {
			head = remove->link;
		}
		else {
			prev->link = remove->link;
		}
		free(remove);
		return head;
	
	}
}
void split_list(ListNode* head, element value) {
	ListNode* p = head;
	ListNode* prev = NULL;
	ListNode* next = search_list(head, value);
	if (next == NULL) {
		error("해당 노드를 찾을 수 없습니다.");
	}
	
	while (p != next) {
		prev = p;
		p = p->link;
	}
	if (prev == NULL) {
		error("쪼갤 수 없는 경우입니다.");
	}
	prev->link = NULL;

	printf("list1: ");
	print_list(head);

	printf("list2: ");
	print_list(next->link);
}

int main(void) {
	ListNode* head = NULL;
	element data;

	strcpy(data.name, "PEACH");
	head = insert_first(head, data);

	strcpy(data.name, "MELON");
	head = insert_first(head, data);

	strcpy(data.name, "MANGO");
	head = insert_first(head, data);

	strcpy(data.name, "LEMON");
	head = insert_first(head, data);

	strcpy(data.name, "BANANA");
	head = insert_first(head, data);

	strcpy(data.name, "KIWI");
	head = insert_first(head, data);

	strcpy(data.name, "APPLE");
	head = insert_first(head, data);

	strcpy(data.name, "head");
	head = insert_first(head, data);
	print_list(head);

	printf("\n삭제 단어: ");
	strcpy(data.name, "LEMON");
	printf("%s\n",data.name);

	split_list(head, data);
	delete(head, data);
	return 0;
}

