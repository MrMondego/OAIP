#include <iostream>
#include <ctime>
using namespace std;

// Функция для генерации случайного массива
void generateRandomArray(int arr[], int n, int minNum, int maxNum) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (maxNum - minNum + 1) + minNum;
    }
}

// Сортировка выбором
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Слияние двух отсортированных массивов в один
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

// Сортировка слиянием
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Функция для просеивания поддерева
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

// Пирамидальная сортировка
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    const int MAX_SIZE = 5000;
    int arr[MAX_SIZE];

    // Массивы размером 1000, 2000, 3000, 4000 и 5000
    int sizes[] = { 1000, 2000, 3000, 4000, 5000 };

    // Заполняем массивы случайными числами и сортируем
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        generateRandomArray(arr, n, 1, 10000);

        // Сортировка выбором
        // Измеряем время выполнения сортировки выбором
        clock_t startSelection = clock();
        selectionSort(arr, n);
        clock_t endSelection = clock();
        double timeSelection = double(endSelection - startSelection) / CLOCKS_PER_SEC;

        // Сортировка слиянием
        generateRandomArray(arr, n, 1, 10000);
        clock_t startMerge = clock();
        mergeSort(arr, 0, n - 1);
        clock_t endMerge = clock();
        double timeMerge = double(endMerge - startMerge) / CLOCKS_PER_SEC;

        // Пирамидальная сортировка
        generateRandomArray(arr, n, 1, 10000);
        clock_t startHeap = clock();
        heapSort(arr, n);
        clock_t endHeap = clock();
        double timeHeap = double(endHeap - startHeap) / CLOCKS_PER_SEC;

        // Выводим результаты
        cout << "Массив размером " << n << ":" << endl;
        cout << "Сортировка выбором: " << timeSelection << " секунд" << endl;
        cout << "Сортировка слиянием: " << timeMerge << " секунд" << endl;
        cout << "Пирамидальная сортировка: " << timeHeap << " секунд" << endl;

        cout << endl;
    }

    return 0;
}