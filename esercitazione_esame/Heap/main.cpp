#include "heap.h"

int main() {
    int *A;
    int dim = 10;
    A = (int *) calloc(dim, sizeof(int));

    auto *Maxpq = new PriorityQueue(A, dim);

    Maxpq->printHeap();
    Maxpq->heapSort();
    Maxpq->insert(1000);
    cout<<endl;
    Maxpq->printHeap();

}