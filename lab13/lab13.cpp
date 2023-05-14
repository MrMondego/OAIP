#include <iostream>
#include <vector>
using namespace std;

class BinaryHeap {
private:
    vector<int> heapArray;

    int getParent(int i) {
        return (i - 1) / 2;
    }

    int getLeftChild(int i) {
        return 2 * i + 1;
    }

    int getRightChild(int i) {
        return 2 * i + 2;
    }

    void heapifyDown(int i) {
        int left = getLeftChild(i);
        int right = getRightChild(i);
        int smallest = i;

        if (left < heapArray.size() && heapArray[left] < heapArray[i])
            smallest = left;

        if (right < heapArray.size() && heapArray[right] < heapArray[smallest])
            smallest = right;

        if (smallest != i) {
            swap(heapArray[i], heapArray[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int i) {
        int parent = getParent(i);

        if (parent >= 0 && heapArray[i] < heapArray[parent]) {
            swap(heapArray[i], heapArray[parent]);
            heapifyUp(parent);
        }
    }

public:
    BinaryHeap() {}

    BinaryHeap(vector<int> unsortedArray) {
        heapArray = unsortedArray;
        for (int i = heapArray.size() / 2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    void push(int element) {
        heapArray.push_back(element);
        heapifyUp(heapArray.size() - 1);
    }

    int extractMin() {
        int root = heapArray[0];
        heapArray[0] = heapArray[heapArray.size() - 1];
        heapArray.pop_back();
        heapifyDown(0);
        return root;
    }

    void extractI(int i) {
        heapArray[i] = heapArray[heapArray.size() - 1];
        heapArray.pop_back();
        if (heapArray[i] < heapArray[getParent(i)])
            heapifyUp(i);
        else
            heapifyDown(i);
    }

    void unionHeap(BinaryHeap& otherHeap) {
        for (int i = 0; i < otherHeap.heapArray.size(); i++)
            heapArray.push_back(otherHeap.heapArray[i]);
        for (int i = heapArray.size() / 2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    void printHeap() {
        for (int i = 0; i < heapArray.size(); i++)
            cout << heapArray[i] << " ";
        cout << endl;
    }
};

int main() {
    vector<int> myArray = { 8, 2, 5, 4, 3, 9 };
    BinaryHeap myHeap(myArray);

    cout << "Current heap: ";
    myHeap.printHeap();

    myHeap.push(1);
    cout << "Heap after push 1: ";
    myHeap.printHeap();

    int minElement = myHeap.extractMin();
    cout << "Heap after extractMin: ";
    myHeap.printHeap();
    cout << "Extracted minimum element: " << minElement << endl;

    myHeap.extractI(0);
    cout << "Heap after extractI(0): ";
    myHeap.printHeap();

    BinaryHeap otherHeap({ 7, 6, 10 });
    cout << "Second heap: ";
    otherHeap.printHeap();
    myHeap.unionHeap(otherHeap);
    cout << "Merged heap: ";
    myHeap.printHeap();

    return 0;
}