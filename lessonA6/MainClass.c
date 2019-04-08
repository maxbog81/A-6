#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int HashString(char str[]) 
{
	int sum = 0;

	for (int i = 0; i < strlen(str); ++i)
		sum += str[i];

	return sum;
}

int main() {
	//setlocale(LC_ALL, "Rus");
	setlocale(LC_ALL, "en_US.UTF-8");

//1. Реализовать простейшую хэш-функцию. На вход функции подается строка, на выходе получается сумма кодов символов.

	unsigned char txt[] = "Hello world!";
	printf("Cумма кодов символов:%d", HashString(txt));
	printf("\n");
	system("pause");
	return 0;
}