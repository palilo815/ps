#include <bits/stdc++.h>
using namespace std;

const int max_N = 10000;

int N, K;
int arr[max_N];
int T[max_N + 1];

int ceil_elem(int l, int r, int key) {
    while (l + 1 < r) {
        int m = (l + r) >> 1;
        T[m] < key ? (l = m) : (r = m);
    }
    return r;
}
int LIS() {
    int len = 1;
    T[1] = arr[0];

    for (int i = 1; i < N; ++i) {
        if (arr[i] < T[1])
            T[1] = arr[i];
        else if (arr[i] > T[len])
            T[++len] = arr[i];
        else
            T[ceil_elem(0, len, arr[i])] = arr[i];
    }
    return len >= K;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int TC; cin >> TC;
    for (int tc = 1; tc <= TC; ++tc) {
        cin >> N >> K;
        for (int i = 0; i < N; ++i)
            cin >> arr[i];
        cout << "Case #" << tc << '\n'
             << LIS() << '\n';
    }
    return 0;
}