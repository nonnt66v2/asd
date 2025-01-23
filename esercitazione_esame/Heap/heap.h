//
// Created by nonnt66 on 20/01/25.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <iostream>
#include <climits>

using namespace std;

int parent(int i);

int left(int i);

int right(int i);

class PriorityQueue {
private:
    int *A;
    int n;

    void caricaHeap();

    void maxHeapify(int i);

    void buildMaxHeap();

    void changeHeapSize(int newSize);

    void increaseKey(int i,int key);

public:
    PriorityQueue();

    PriorityQueue(int *A, int n);

    void heapSort();

    void printHeap();

    void insert(int num);


};

typedef PriorityQueue pq;

#endif //HEAP_HEAP_H

