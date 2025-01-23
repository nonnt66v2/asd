#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace  std;


int parent(int i){ return (i-1)/2; }
int left(int i){ return 2*i+1; }
int right(int i){ return 2*i+2; }
class priorityQueue{
    int *A;
    int n;
    void maxHeapify(int i);
    void buildMaxHeap();
public:
    priorityQueue(int *A, int heapSize);
    priorityQueue();
    void insert(int key);
    int max();
    int extractMax();
    void increasePriority(int i, int key);
//utilities
    void changeHeapSize(int newsize);
    void print();
};

//Implementation
typedef priorityQueue pq;
pq::priorityQueue(int *arr, int heapSize){
    this->n = heapSize;
    this->A = new int[n];
    for(int i=0; i<n; i++)
        A[i] = arr[i];
    buildMaxHeap();
}
pq::priorityQueue(){
    A = nullptr;
    n = 0;

}
void pq::maxHeapify(int i){
    int l = left(i);
    int r = right(i);
    int max;
    max = (l<n && A[l]>A[i]) ? l : i;
    max = (r<n && A[r]>A[max]) ? r : max;
    if(max != i){
        swap(A[i],A[max]);
        maxHeapify(max);
    }
}
void pq::buildMaxHeap(){
    for(int i=(n/2)-1; i>=0; i--)
        maxHeapify(i);
}
void pq::insert(int key){
    changeHeapSize(n+1);
    A[n-1] = -INT_MAX;
    increasePriority(n-1,key);
}
int pq::max(){
    return A[0];
}

int pq::extractMax(){
    if(n<1){
        std::cout<<"heap underflow";
        exit(1);
    }
    int max = A[0];
    A[0] = A[n-1];
    changeHeapSize(n-1);
    maxHeapify(0);
    return max;
}
void pq::increasePriority(int i, int key){
    if(key<A[i]){
        std::cout<<"key must be greater than current value";
        exit(1);
    }
    A[i] = key;
    while(i>0 && A[parent(i)] < A[i]){
        swap(A[i],A[parent(i)]);
        i = parent(i);
    }
}
//Other
void pq::changeHeapSize(int newsize){
    int *B = new int[newsize];
    for(int i=0; i<newsize; i++){
        if(i<n)
            B[i] = A[i];
        else
            B[i] = 0;
    }
    n = newsize;
    delete[] A;
    A = B;
}

void pq::print() {
    for(int i=0;i<n;i++){
        cout<<"["<<i<<"] = "<<A[i]<<endl;
    }
}

int main(){
    priorityQueue *p = new priorityQueue();
    p->insert(1);
    p->insert(2);
    p->insert(3);
    p->insert(4);
    p->insert(5);
    p->insert(2);
    p->insert(3);
    p->insert(4);
    p->insert(5);
    p->insert(2);
    p->insert(3);
    p->insert(4);
    p->insert(5);
    p->insert(2);
    p->insert(3);
    p->insert(4);
    p->insert(5);
    cout<<"massimo = "<<p->extractMax()<<endl;
    p->print();
}


