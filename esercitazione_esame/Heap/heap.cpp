//
// Created by nonnt66 on 20/01/25.
//


#include "heap.h"


int left(int i){return (i+1)*2;}
int right(int i){return (i+2)*2;}
int parent(int i){return (i-1)/2;}

void PriorityQueue::maxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int massimo;
    l < n && A[l] > A[i] ? massimo = l : massimo = i;
    if (r < n && A[r] > A[massimo]) massimo = r;
    if (massimo != i) {
        std::swap(A[i], A[massimo]);
        maxHeapify(massimo);
    }
}
void pq::caricaHeap() {
    for(int i=0;i<n;i++){
        this->A[i] = rand()%(10-1)+1;
    }
}

PriorityQueue::PriorityQueue() {
    this->n = rand()%(20-10)+10;
    this->A = (int*)calloc(n,sizeof(int));
    caricaHeap();
    buildMaxHeap();
}

PriorityQueue::PriorityQueue(int *A,int n) {
    this->A = A;
    this->n = n;
    caricaHeap();
    buildMaxHeap();

}

void pq::buildMaxHeap() {
    int dim = n/2;
    for(int i=dim-1;i>=0;i--){
        maxHeapify(i);
    }
}

void pq::heapSort() {
    buildMaxHeap();
    int dim = n;
    for(int i=n-1;i>=0;i--){
        swap(A[0],A[i]);
        dim--;
        maxHeapify(i);
    }
}

void pq::printHeap() {
    for(int i=0;i<n;i++){
        cout<<"Heap["<<i<<"]: "<<A[i]<<endl;
    }
}

void pq::insert(int num) {
    changeHeapSize(n+1);
    A[n-1] = -INT_MAX;
    increaseKey(n-1,num);
}

void PriorityQueue::changeHeapSize(int newSize) {
    int *B = new int[newSize];
    for(int i=0;i<newSize;i++){
        if(i<n) B[i] = A[i];
        else B[i] = -INT_MAX;
    }
    n = newSize;
    delete [] A;
    A = B;
}

void PriorityQueue::increaseKey(int i, int key) {
    if(A[i]>key){
        cout<<"impossibile eseguire increase key\n";
        exit(1);
    }
    A[i] = key;
    while(i>0 && A[parent(i)]<A[i]){
        swap(A[i],A[parent(i)]);
        i = parent(i);
    }
}
