#include <iostream>
#include <vector>
using namespace std;

const int EMPTY = -1;

class HashTable {
private:
    vector<int> keys;
    vector<int> values;
    int hashTableSize;

    int hashFunction(int key) {
        // Простая хеш-функция
        return key % hashTableSize;
    }

public:
    HashTable(int size) {
        hashTableSize = size;
        keys.assign(hashTableSize, EMPTY);
        values.assign(hashTableSize, EMPTY);
    }

    void insert(int key, int value) {
        int hash = hashFunction(key);
        int i = 1;

        while (keys[hash] != EMPTY && keys[hash] != key && i < hashTableSize) {
            hash = (hashFunction(key) + i) % hashTableSize;
            i++;
        }

        if (keys[hash] == EMPTY || keys[hash] == key) {
            keys[hash] = key;
            values[hash] = value;
        }
        else {
            cout << "Хэш-таблица переполнена." << endl;
        }
    }

    void remove(int key) {
        int hash = hashFunction(key);
        int i = 1;

        while (keys[hash] != EMPTY && i < hashTableSize) {
            if (keys[hash] == key) {
                keys[hash] = EMPTY;
                values[hash] = EMPTY;
                return;
            }
            hash = (hashFunction(key) + i) % hashTableSize;
            i++;
        }
        cout << "Элемент с ключом " << key << " не найден." << endl;
    }

    int get(int key) {
        int hash = hashFunction(key);
        int i = 1;

        while (keys[hash] != EMPTY && i <= hashTableSize) {
            if (keys[hash] == key) {
                return values[hash];
            }
            hash = (hashFunction(key) + i) % hashTableSize;
            i++;
        }
        cout << "Элемент с ключом " << key << " не найден." << endl;
        return EMPTY;
    }

    void printHashTable() {
        for (int i = 0; i < hashTableSize; i++) {
            if (keys[i] != EMPTY) {
                cout << "Ключ: " << keys[i] << ", Значение: " << values[i] << endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    // Создание хеш-таблицы размером 16
    HashTable hashTable1(16);

    // Вставка элементов со значением, равным ключу
    for (int i = 0; i < 20; i++) {
        hashTable1.insert(i, i);
    }

    // Вывод элементов хеш-таблицы
    cout << "Хеш-таблица размером 16:" << endl;
    hashTable1.printHashTable();
    cout << endl;

    // Создание хеш-таблицы размером 32
    HashTable hashTable2(32);

    // Вставка элементов со значением, равным ключу
    for (int i = 0; i < 40; i++) {
        hashTable2.insert(i, i);
    }

    // Вывод элементов хеш-таблицы
    cout << "Хеш-таблица размером 32:" << endl;
    hashTable2.printHashTable();
    cout << endl;

    // Создание хеш-таблицы размером 64
    HashTable hashTable3(64);

    // Вставка элементов со значением, равным ключу
    for (int i = 0; i < 80; i++) {
        hashTable3.insert(i, i);
    }

    // Вывод элементов хеш-таблицы
    cout << "Хеш-таблица размером 64:" << endl;
    hashTable3.printHashTable();
    cout << endl;

    return 0;
}