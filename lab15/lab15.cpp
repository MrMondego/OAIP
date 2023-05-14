#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int EMPTY = -1;

class Client {
public:
    int accountNumber = 0;
    string name;
};

class Node {
public:
    Client client;
    Node* next;

    Node(int accountNumber, string name) {
        client.accountNumber = accountNumber;
        client.name = name;
        next = NULL;
    }
};

class HashTable {
private:
    vector<Node*> table;
    int hashTableSize;

    int hashFunction(int accountNumber) {
        // Хеш-функция на базе исключающего ИЛИ
        int hash = 0;
        for (int i = 0; i < sizeof(accountNumber); i++) {
            hash ^= ((accountNumber >> (i * 8)) & 0xFF);
        }
        return hash % hashTableSize;
    }

public:
    HashTable(int size) {
        hashTableSize = size;
        table.assign(hashTableSize, NULL);
    }

    void insert(int accountNumber, string name) {
        int hash = hashFunction(accountNumber);
        Node* node = table[hash];

        if (node == NULL) {
            table[hash] = new Node(accountNumber, name);
            return;
        }

        while (node->next != NULL) {
            node = node->next;
        }

        node->next = new Node(accountNumber, name);
    }

    void remove(int accountNumber) {
        int hash = hashFunction(accountNumber);
        Node* node = table[hash];

        if (node == NULL) {
            cout << "Клиент с номером счета " << accountNumber << " не найден." << endl;
            return;
        }

        if (node->client.accountNumber == accountNumber) {
            table[hash] = node->next;
            delete node;
            return;
        }

        Node* prev = node;
        node = node->next;

        while (node != NULL) {
            if (node->client.accountNumber == accountNumber) {
                prev->next = node->next;
                delete node;
                return;
            }

            prev = node;
            node = node->next;
        }

        cout << "Клиент с номером счета " << accountNumber << " не найден." << endl;
    }

    void printClient(int accountNumber) {
        int hash = hashFunction(accountNumber);
        Node* node = table[hash];

        while (node != NULL) {
            if (node->client.accountNumber == accountNumber) {
                cout << "Клиент с номером счета " << accountNumber << " - " << node->client.name << endl;
                return;
            }

            node = node->next;
        }

        cout << "Клиент с номером счета " << accountNumber << " не найден." << endl;
    }

    void printHashTable() {
        for (int i = 0; i < hashTableSize; i++) {
            Node* node = table[i];
            if (node != NULL) {
                cout << "Хеш " << i << ": ";
                while (node != NULL) {
                    cout << "[" << node->client.accountNumber << "," << node->client.name << "]";
                    node = node->next;
                }
                cout << endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    HashTable myTable(10);

    myTable.insert(123456, "Ivan Petrov");
    myTable.insert(654321, "Maria Ivanova");
    myTable.insert(345678, "John Smith");

    myTable.printClient(123456);
    myTable.printClient(999999);

    return 0;
}