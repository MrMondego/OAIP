#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    const int MAX_SIZE = 100;
    int A[MAX_SIZE], B[MAX_SIZE], C[MAX_SIZE];
    int nA, nB, nC = 0;

    // ���� �������� A � B
    cout << "������� ������ ������� A: ";
    cin >> nA;
    cout << "������� ������ A: ";
    for (int i = 0; i < nA; i++) {
        cin >> A[i];
    }

    cout << "������� ������ ������� B: ";
    cin >> nB;
    cout << "������� ������ B: ";
    for (int i = 0; i < nB; i++) {
        cin >> B[i];
    }

    // ������� ������������ ������� ������� B
    int maxB = *max_element(B, B + nB);

    // �������� �������� �� A � C, ���� ��� ������ maxB
    for (int i = 0; i < nA; i++) {
        if (A[i] > maxB) {
            C[nC++] = A[i];
        }
    }

    // ��������� ������ C �� �������� � ������� ���������� ���������
    for (int i = 0; i < nC - 1; i++) {
        for (int j = 0; j < nC - i - 1; j++) {
            if (C[j] < C[j + 1]) {
                swap(C[j], C[j + 1]);
            }
        }
    }

    // ������� ��������������� ������ C
    cout << "������ C, ��������������� �� ��������: ";
    for (int i = 0; i < nC; i++) {
        cout << C[i] << " ";
    }
    cout << endl;

    // ��������� ������ C �� �������� � ������� ���������� ������� ��������
    for (int i = 1; i < nC; i++) {
        int temp = C[i];
        int j = i - 1;
        while (j >= 0 && C[j] < temp) {
            C[j + 1] = C[j];
            j--;
        }
        C[j + 1] = temp;
    }

    // ������� ��������������� ������ C
    cout << "������ C, ��������������� �� �������� � ������� ���������� ������� ��������: ";
    for (int i = 0; i < nC; i++) {
        cout << C[i] << " ";
    }
    cout << endl;

    return 0;
}