#include <bits/stdc++.h>
using namespace std;

const int max_D = 300000;

int arr[max_D];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int D, N; cin >> D >> N;

    int pizza = INT_MAX;
    for (int i = 0; i < D; ++i) {
        int dia; cin >> dia;
        if (dia < pizza) pizza = dia;
        arr[i] = pizza;
    }
    
    int pos = D - 1;
    while (N--) {
        cin >> pizza;
        while (pos >= 0 && arr[pos] < pizza) --pos;
        if (pos < 0) { cout << 0; return 0; }
        --pos;
    }
    cout << pos + 2;
    return 0;
}