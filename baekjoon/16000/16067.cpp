#include <bits/stdc++.h>
using namespace std;

const int mxM = 1e6;

int id[mxM + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    int one1 = 0, one2 = 0;
    for (int i = 1, m; i <= N; ++i) {
        cin >> m;
        id[m] = i;
        if (m == 1)
            (one1 ? one2 : one1) = i;
    }

    if (one1 && one2) {cout << one1 << ' ' << one2; return 0;}
    for (int i = 1, j = 2; j <= mxM; swap(i, j)) {
        if (id[i] && id[j]) {cout << id[i] << ' ' << id[j]; return 0;}
        i += j;
    }
    cout << "impossible";
    return 0;
}