#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000000;

int arr[max_N * 2 + 1];
int p[max_N * 2 + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> arr[2 * i + 1];

    int l = 0, r = -1;
    N = 2 * N + 1;
    for (int i = 0; i < N; ++i) {
        int k;
        if (i > r) k = 0;
        else k = min(p[l + r - i], r - i);

        while (i - k > 0 && i + k + 1 < N && arr[i - k - 1] == arr[i + k + 1])
            ++k;

        p[i] = k;
        if (i + k > r)
            r = i + k, l = i - k;
    }

    int Q; cin >> Q;
    while (Q--) {
        int s, e; cin >> s >> e;
        int g = e - s;
        cout << (p[s * 2 - 1 + g] >= g) << '\n';
    }
    return 0;
}