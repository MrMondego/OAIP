#include <stdio.h>
#include <iostream>
#include <vector>

FILE* f;
FILE* f2;

void z1() {
	setlocale(LC_ALL, "");
	#define N 100
	int arr[N];
	int i, j, x;

	if (fopen_s(&f, "fileA.txt", "r") != 0) {
		perror("Произошла ошибка при открытии файла!\n");
		exit(EXIT_FAILURE);
	}
	if (fscanf_s(f, "%d", &x) != 1) {
		printf_s("Не удалось прочитать первый элемент");
		exit(EXIT_FAILURE);
	}
	printf("x: %d\n", x);
	for (i = 0; i < N; i++) {
		if (fscanf_s(f, "%d", &arr[i]) != 1)
			break;
	}
	for (j = 0; j < i; j++) {
		printf("numbers[%d] --> %d\n", j, arr[j]);
	}
	fclose(f);

	int sred = 0, fnd_i = 0, fnd_j = 1;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if ((i != j) && (abs(x - (arr[i] + arr[j]) / 2) < abs(x - (arr[fnd_i] + arr[fnd_j]) / 2))) {
				fnd_i = i;
				fnd_j = j;
			}
		}
	}
	printf_s("Первый элемент: %d\nВторой элемент: %d\n", arr[fnd_i], arr[fnd_j]);
}
void z2() {
	int x[10], i;
	int k[10];
	char* estr;
	char str[50];
	if (fopen_s(&f, "F1.txt", "r") != 0) {
		perror("Произошла ошибка при открытии файла!\n");
		exit(EXIT_FAILURE);
	}
	if (fopen_s(&f2, "F2.txt", "w") != 0) {
		perror("Произошла ошибка при открытии файла!\n");
		exit(EXIT_FAILURE);
	}

	const char ds[] = "0123456789";
	for (int i = 0; i < 5; i++) {
		if (fgets(str, sizeof(str), f) == NULL)
			break;
		
		if (strpbrk(str, ds) == NULL) {
			if (fputs(str, f2) == EOF)
				break;
		}
	}
	if (fclose(f) == EOF)
		printf("Ошибка закрытия\n");
	if (fclose(f2) == EOF)
		printf("Ошибка закрытия\n");
}

int main() {
	std::vector<void(*)()> choice = { z1, z2 };
	int enter = 0;

	while (true) {
		setlocale(LC_ALL, "Rus");
		std::cout << "Доступные задания: ";
		for (int i = 0; i < choice.size(); i++) std::cout << i + 1 << " ";
		std::cout << std::endl;
		std::cin >> enter;
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cin >> enter;
		}
		if (enter == 0) break;
		if (enter > choice.size()) {
			std::cout << "Неверный ввод! Попробуйте ещё раз\n";
			continue;
		}
		system("cls");
		choice[enter - 1]();
		system("pause");
		system("cls");
	}
}