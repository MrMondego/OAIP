#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    const int MAX_SIZE = 100;
    int A[MAX_SIZE], B[MAX_SIZE], C[MAX_SIZE];
    int nA, nB, nC = 0;

    // Ввод массивов A и B
    cout << "Введите размер массива A: ";
    cin >> nA;
    cout << "Введите массив A: ";
    for (int i = 0; i < nA; i++) {
        cin >> A[i];
    }

    cout << "Введите размер массива B: ";
    cin >> nB;
    cout << "Введите массив B: ";
    for (int i = 0; i < nB; i++) {
        cin >> B[i];
    }

    // Находим максимальный элемент массива B
    int maxB = *max_element(B, B + nB);

    // Копируем элементы из A в C, если они больше maxB
    for (int i = 0; i < nA; i++) {
        if (A[i] > maxB) {
            C[nC++] = A[i];
        }
    }

    // Сортируем массив C по убыванию с помощью сортировки пузырьком
    for (int i = 0; i < nC - 1; i++) {
        for (int j = 0; j < nC - i - 1; j++) {
            if (C[j] < C[j + 1]) {
                swap(C[j], C[j + 1]);
            }
        }
    }

    // Выводим отсортированный массив C
    cout << "Массив C, отсортированный по убыванию: ";
    for (int i = 0; i < nC; i++) {
        cout << C[i] << " ";
    }
    cout << endl;

    // Сортируем массив C по убыванию с помощью сортировки простой вставкой
    for (int i = 1; i < nC; i++) {
        int temp = C[i];
        int j = i - 1;
        while (j >= 0 && C[j] < temp) {
            C[j + 1] = C[j];
            j--;
        }
        C[j + 1] = temp;
    }

    // Выводим отсортированный массив C
    cout << "Массив C, отсортированный по убыванию с помощью сортировки простой вставкой: ";
    for (int i = 0; i < nC; i++) {
        cout << C[i] << " ";
    }
    cout << endl;

    return 0;
}