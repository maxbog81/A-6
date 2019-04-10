#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdlib.h>

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))

typedef int T;
typedef struct Node {
	T data;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
} Node;
// Распечатка двоичного дерева в виде скобочной записи
void printTree(Node *root) {
	if (root)
	{
		printf("%d", root->data);
		if (root->left || root->right)
		{
			printf("(");

			if (root->left)
				printTree(root->left);
			else
				printf("NULL");
			printf(",");

			if (root->right)
				printTree(root->right);
			else
				printf("NULL");
			printf(")");
		}
	}
}

// Создание нового узла
Node* getFreeNode(T value, Node *parent) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->left = tmp->right = NULL;
	tmp->data = value;
	tmp->parent = parent;
	return tmp;
}

// Вставка узла
void insert(Node **head, int value) {
	Node *tmp = NULL;
	if (*head == NULL)
	{
		*head = getFreeNode(value, NULL);
		return;
	}

	tmp = *head;
	while (tmp)
	{
		if (value > tmp->data)
		{
			if (tmp->right)
			{
				tmp = tmp->right;
				continue;
			}
			else
			{
				tmp->right = getFreeNode(value, tmp);
				return;
			}
		}
		else if (value < tmp->data)
		{
			if (tmp->left)
			{
				tmp = tmp->left;
				continue;
			}
			else
			{
				tmp->left = getFreeNode(value, tmp);
				return;
			}
		}
		else
		{
			exit(2);                     // Дерево построено неправильно
		}
	}
}

void preOrderTravers(Node* root) {
	if (root) {
		printf("%d ", root->data);
		preOrderTravers(root->left);
		preOrderTravers(root->right);
	}
}

void InOrderTravers(Node* root) {
	if (root) {		
		preOrderTravers(root->left);
		printf("%d ", root->data);
		preOrderTravers(root->right);
	}
}

void PostOrderTravers(Node* root) {
	if (root) {
		preOrderTravers(root->left);		
		preOrderTravers(root->right);
		printf("%d ", root->data);
	}
}

int HashString(char str[]) 
{
	int sum = 0;

	for (int i = 0; i < strlen(str); ++i)
		sum += str[i];

	return sum;
}
//Поиск

Node *getNodeByValue(Node *root, T value) {
	while (root) {
		if (CMP_GT(root->data, value)) {
			root = root->left;
			continue;
		}
		else if (CMP_LT(root->data, value)) {
			root = root->right;
			continue;
		}
		else {
			//return root;			
			return root->data;
		}
	}
	return NULL;
}

int main() {
	//setlocale(LC_ALL, "Rus");
	setlocale(LC_ALL, "en_US.UTF-8");

//1. Реализовать простейшую хэш-функцию. На вход функции подается строка, на выходе получается сумма кодов символов.

	unsigned char txt[] = "Hello world!";
	printf("Cумма кодов символов:%d", HashString(txt));
	printf("\n");

	//2.	Переписать программу, реализующее двоичное дерево поиска :
	//a.Добавить в него обход дерева различными способами.
	//	b.Реализовать поиск в нём.
	//	c.	*Добавить в программу обработку командной строки с помощью которой можно указывать, из какого файла считывать данные, каким образом обходить дерево.

	Node *Tree = NULL;

	FILE *file;

	char input_file_name[81];// имя файла
	printf("Введите имя файла:");
	scanf("%s", input_file_name);
	file = fopen(input_file_name, "rt");
	if (file == NULL)
	{
		file = fopen("data.txt", "r");
		if (file == NULL)
		{
			puts("Can't open file!");
			exit(1);
		}
	}

	//FILE* file = fopen("data.txt", "r");
	//if (file == NULL)
	//{
	//	puts("Can't open file!");
	//	exit(1);
	//}
	int count;
	fscanf(file, "%d", &count);          // Считываем количество записей
	int i;
	for (i = 0; i < count; i++)
	{
		int value;
		fscanf(file, "%d", &value);
		insert(&Tree, value);
	}
	fclose(file);
	printTree(Tree);
	int a2 = 0;
	printf("\nВведите как обходить дерево 1:pre-order 2:in-order 3:post-order: ");
	scanf("%d", &a2);
	switch (a2)
	{
	case 1:
			printf("\nPreOrderTravers:");
			preOrderTravers(Tree);
			break;
	case 2:
		printf("\nInOrderTravers:");
		InOrderTravers(Tree);
		break;
	case 3:
		printf("\nPostOrderTravers:");
		PostOrderTravers(Tree);
		break;
	default:
		break;
	}
	//Поиск
	printf("\nВведите число для поиска: ");
	int a = 0;
	scanf("%d", &a);
	printf("%d\n", getNodeByValue(Tree, i));

	printf("\n");
	system("pause");
	return 0;
}