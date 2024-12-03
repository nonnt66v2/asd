#include <iostream>
#include <climits>

using namespace std;

class priorityQueue {
    int *A;
    int n;


    void maxHeapify(int i);

    void buildMaxHeap();

public:

    priorityQueue(int *A, int heapSize);

    priorityQueue();

    int parent(int i) {
        return (i - 1) / 2;
    }

    int left(int i) {
        return (i * 2) + 1;
    }

    int right(int i) {
        return (i * 2) + 2;
    }


    void insert(int key);

    int max();

    int extractMax();

    void incresePriority(int i, int key);

    void changeHeapSize(int newSize);

    void print();

    /*void buildMaxHeap(int *vet);

    void heapSort(int *vet);*/
};

typedef priorityQueue pq;

pq::priorityQueue(int *A, int heapSize) {
    this->n = heapSize;
    this->A = new int[n];
    for (int i = 0; i < n; i++) {
        this->A[i] = A[i];
    }
    buildMaxHeap();

}

pq::priorityQueue() {
    A = nullptr;
    n = 0;
}

void pq::maxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int massimo;
    if (l < n && A[l] > A[i]) massimo = l;
    else massimo = i;
    if (r < n && A[r] > A[massimo]) massimo = r;
    if (massimo != i) {
        swap(A[i], A[massimo]);
        maxHeapify(massimo);
    }
}

void pq::insert(int key) {
    changeHeapSize(n + 1);
    A[n - 1] = INT_MIN;
    incresePriority(n - 1, key);
}

void pq::incresePriority(int i, int key) {
    if (key < A[i]) {
        cout << "la chiave deve essere più grande del valore attuale\n";
        exit(-1);
    }
    A[i] = key;
    while (i > 0 && A[i] > A[parent(i)]) {
        swap(A[i], A[parent(i)]);
        i = parent(i);
    }
}

int pq::extractMax() {
    if (n < 1) {
        cout << "heap vuoto";
        exit(-1);
    }
    int max = A[0];
    A[0] = A[n - 1];
    changeHeapSize(n - 1);
    maxHeapify(0);
    return max;
}

void pq::changeHeapSize(int newSize) {
    int *B = new int[newSize];
    for (int i = 0; i < newSize; i++) {
        if (i < n) B[i] = A[i];
        else B[i] = 0;
    }
    n = newSize;
    delete[] A;
    A = B;
}


/*
void buildMaxHeap(int *vet,int n) {

}

void heapSort(int *vet,int n) {
    for (int i = n - 1; i >= 1; i--) {
        swap(vet[0], vet[i]);
        n--;
        maxHeapify(0);
    }
}
*/

void pq::print() {
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void priorityQueue::buildMaxHeap() {
    for (int i = (n / 2) - 1; i >= 0; i--) {
        maxHeapify(i);
    }
}

int main() {
    const int N = 10;
    int vet[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7} /*=(int *) calloc(N, sizeof(int))*/;
    priorityQueue coda = *new priorityQueue(vet, N);
    coda.print();
    coda.extractMax();
    coda.print();
    coda.insert(55);
    coda.print();
    cout << endl;

}
