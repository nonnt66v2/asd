#include <iostream>
#include <ctime>
#define N 6000

using namespace std;


/***
 *
 * @param vetA
 * @param p
 * @param r
 * @return
 */
int partition(int *vetA, int p, int r) {
    int x = vetA[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (vetA[j] <= x) {
            i++;
            swap(vetA[i], vetA[j]);
        }
    }
    swap(vetA[i + 1], vetA[r]);
    return ++i;
}

/***
 *
 * @param vetA
 * @param p
 * @param r
 */
void Quicksort(int *vetA, int p, int r) {
    if (p < r) {
        int q = partition(vetA, p, r);
        Quicksort(vetA, p, q - 1);
        Quicksort(vetA, q + 1, r);
    }
}

int randomizedPartition(int *vetA, int p, int r) {
    int i = (rand() % (r - p) + p);
    swap(vetA[i], vetA[r]);
    return partition(vetA, p, r);
}

void randomizedQuicksort(int *vetA, int p, int r) {
    if (p < r) {
        int q = randomizedPartition(vetA, p, r);
        randomizedQuicksort(vetA, p, q - 1);
        randomizedQuicksort(vetA, q + 1, r);
    }
}

int main() {
    int *vet = (int *) calloc(N, sizeof(int));
    int p = 0;
    int r = N - 1;
    for (int i = 0; i < N; i++) {
        vet[i] = rand() % (90 - 1) + 1;
    }
    clock_t t0, t1;
    t0 = clock();
    Quicksort(vet, p, r);
    t1 = clock();
    double misura  = ((double)t1-t0)/CLOCKS_PER_SEC;
    cout << "tempo impiegato Quicksort [" <<misura<< "] secondi\n";

    clock_t t2, t3;
    t2 = clock();
    randomizedQuicksort(vet, p, r);
    t3 = clock();
    misura  = ((double)t3-t2)/CLOCKS_PER_SEC;
    cout << "tempo impiegato Randomized Quicksort [" << misura<< "] secondi";
    /*for (int i = 0; i < N; i++) {
        cout << vet[i] << " ";
    }*/
    free(vet);
    return 0;

}
