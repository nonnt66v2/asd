#include <iostream>
#include <stdlib.h>

using namespace std;

void bubbleSort(int *vet, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (vet[i] < vet[j]) swap(vet[i], vet[j]);
        }
    }
}

int main() {
    const int N = 1000;
    int *vet = (int *) calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        vet[i] = rand() % (250 - 25) + 25;
    }
    clock_t t0,t1;
    t0 = clock();
    bubbleSort(vet, N);
    t1 = clock();
    double tempo = (double)(t1-t0)/CLOCKS_PER_SEC;
    for (int i = 0; i < N; i++) {
        cout << vet[i] << " ";
    }
    cout<<"\nl'algoritmo ha impiegato ["<<tempo<<"] secondi\n";

}
