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

TreeNode* search(TreeNode* node, element data) //Ž�� �Լ�
{
	if (node == NULL) //node�� null�̸� null����
		return NULL;

	if (strcmp(data.name, node->key.name) == 0) //key�� ����Ű�� ���� �����ϸ� node ����
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

void inorder(TreeNode* root) //���� ��ȸ
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
	element e; //����ó ����
	char input;
	TreeNode* root = NULL; //���� Ʈ�� = NULL
	TreeNode* temp; //�˻� ��带 ��ȯ ���� ���

	//����(i), Ž��(s), ���(p), ����(d), ����(q)
	do {
		printf("����(i), Ž��(s), ���(p), ����(d), ����(q): ");
		scanf("%c", &input);
		getchar();
		int count = Count(root);
		switch (input) {
		case 'i' :
			printf("�̸�: ");
			scanf("%s", e.name);
			printf("��ȭ ��ȣ: ");
			scanf("%s", e.phone);
			getchar();
			root = insert_node(root, e); 
			break;
		

		case's':
			printf("�˻� �̸� : ");
			scanf("%s", e.name);
			getchar();
			temp = search(root, e);
			printf("'%s'�� ��ȭ��ȣ: %s\n", e.name, temp->key.phone);
			break;


		case'p':
			printf("��ȭ��ȣ ����: %d\n", count);
			inorder(root);
			printf("\n");
			break;
		
			
		case'd':
			printf("���� �� ����ó�� �̸�: ");
			scanf("%s", e.name);
			getchar();
			delete_node(root, e);
			break;
		case 'q':
			break;
		default:
			printf("�ٽ� �Է����ּ���.\n");
		}
	} while (input != 'q');
	printf("����");
	return 0;
}