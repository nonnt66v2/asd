#include <iostream>
#include "vector"
using namespace std;

int max (int *A,int N){
    int max=A[0];
    for(int i=1;i<N;i++){
        if(A[i] > max) max = A[i];
    }
    return max;
}
void insertionSort(int *A,int N){
    for(int j=1;j<N;j++){
        int key = A[j];
        int i=j-1;
        while (i>0 && A[i]>key){
            A[i+1] = A[i];
            i--;
        }
        A[i+1] =key;
    }
}
void bucketSort(int *A, int N){
    vector<int> bucket[N];
    int maxp1 = max(A,N)+1;
    for(int i=0;i<N-1;i++){
        bucket[N*(A[i]/maxp1)].push_back(A[i]);
    }

    int *B;
    int m;
    for(int i=0;i<N;i++){
        B = bucket[i].data();
        m = bucket[i].size();
        insertionSort(B,m);
    }
    int k=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<bucket[i].size();j++){
            A[k++] = bucket[i][j];
        }
    }

}
int main() {
    const int N = 10;
    int A[N] = {9,8,7,6,5,4,3,2,1,0};
    bucketSort(A,N);
    for(int i=0;i<N;i++){
        cout<<A[i]<< " ";
    }
}
