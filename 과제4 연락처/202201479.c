#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element
{
	char name[100];
	char phone[14];
}element;

typedef struct TreeNode
{
	element key;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* search(TreeNode* node, element data) //탐색 함수
{
	if (node == NULL) //node가 null이면 null리턴
		return NULL;

	if (strcmp(data.name, node->key.name) == 0) //key가 가리키는 값이 동일하면 node 리턴
		return node;
	else if (strcmp(data.name, node->key.name) < 0)
		return search(node->left, data);
	else
		return search(node->right, data);
}

TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	strcpy(temp->key.name, item.name);
	strcpy(temp->key.phone , item.phone);
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, element data)
{
	if (node == NULL)
		return new_node(data); 

	if (strcmp(data.name, node->key.name) < 0)
		node->left = insert_node(node->left, data);
	else if (strcmp(data.name, node->key.name) > 0)
		node->right = insert_node(node->right, data);
	else
		strcpy(node->key.phone,  data.phone);

	return node;
}

TreeNode* max_value_node(TreeNode* node)
{
	TreeNode* current = node;

	while (current->right != NULL)
		current = current->right;
	return current;
}

TreeNode* delete_node(TreeNode* root, element data)
{
	if (root == NULL)
		return root;

	if (strcmp(data.name, root->key.name) < 0)
		root->left = delete_node(root->left, data);
	else if (strcmp(data.name, root->key.name) > 0)
		root->right = delete_node(root->right, data);
	else
	{
		if (root->left == NULL)
		{
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}

		TreeNode* temp = max_value_node(root->left);

		root->key = temp->key;
		root->right = delete_node(root->left, temp->key);
	}

	return root;
}

void inorder(TreeNode* root) //중위 순회
{
	if (root)
	{
		inorder(root->left);
		printf("[%s: %s]\n", root->key.name, root->key.phone);
		inorder(root->right);
	}
}

int Count(TreeNode* root) {
	if (root == NULL) {
		return 0;
	}
	else
		return 1 + Count(root->left) + Count(root->right);
}

int main(void)
{
	element e; //연락처 정보
	char input;
	TreeNode* root = NULL; //최초 트리 = NULL
	TreeNode* temp; //검색 노드를 반환 받을 노드

	//삽입(i), 탐색(s), 출력(p), 삭제(d), 종료(q)
	do {
		printf("삽입(i), 탐색(s), 출력(p), 삭제(d), 종료(q): ");
		scanf("%c", &input);
		getchar();
		int count = Count(root);
		switch (input) {
		case 'i' :
			printf("이름: ");
			scanf("%s", e.name);
			printf("전화 번호: ");
			scanf("%s", e.phone);
			getchar();
			root = insert_node(root, e); 
			break;
		

		case's':
			printf("검색 이름 : ");
			scanf("%s", e.name);
			getchar();
			temp = search(root, e);
			printf("'%s'의 전화번호: %s\n", e.name, temp->key.phone);
			break;


		case'p':
			printf("전화번호 개수: %d\n", count);
			inorder(root);
			printf("\n");
			break;
		
			
		case'd':
			printf("삭제 할 연락처의 이름: ");
			scanf("%s", e.name);
			getchar();
			delete_node(root, e);
			break;
		case 'q':
			break;
		default:
			printf("다시 입력해주세요.\n");
		}
	} while (input != 'q');
	printf("종료");
	return 0;
}