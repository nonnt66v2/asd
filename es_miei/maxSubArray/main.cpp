#include <iostream>
#include <climits>


using namespace std;



int max(int a, int b, int c) {
    return max(max(a, b), c);
}

int maxCrossSubArray(int *a, int l, int m, int h) {
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; i--) {
        sum += a[i];
        if (sum > left_sum) left_sum = sum;
    }
    int right_sum = INT_MIN;
    sum = 0;
    for (int i = m; i <= h; i++) {
        sum += a[i];
        if (sum > right_sum) right_sum = sum;
    }
    return max(right_sum + left_sum - a[m], left_sum, right_sum);

}

int maxSubArraySum(int *a, int l, int h) {
    if (l > h) {
        return INT_MIN;
    }

    if (l == h) return a[1];

    int m = (h + l) / 2;

    return max(maxSubArraySum(a, l, m - 1), maxSubArraySum(a, m + 1, h), maxCrossSubArray(a, l, m, h));
}

int main() {
    const int N = 10;
    int *vet=(int*)calloc(N,sizeof(int));
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) vet[i] = -(rand() % 250);
        else vet[i] = rand() % (250 - 25) + 25;
    }
    clock_t t0, t1;
    t0 = clock();
    int somma = maxSubArraySum(vet, 0, N-1);
//    int somma = max(1, 2, 3);
    t1 = clock();
    for (int i = 0; i < N; i++) {
        cout << vet[i] << " ";
    }
    cout << "\nsomma massima: [" << somma << "]";
    cout << "\nTempo di esecuzione: " << (double) (t1 - t0) / CLOCKS_PER_SEC << " secondi";

}
