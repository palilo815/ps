#include <bits/stdc++.h>
using namespace std;

int a[9];
bool sieve[9001];

int main() {
    sieve[0] = sieve[1] = true;
    for (int i = 2; i * i < 9001; ++i)
        if (!sieve[i])
            for (int j = i * i; j < 9001; j += i)
                sieve[j] = true;

    int N, M; cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    set<int> ans;
    int C = (1 << M) - 1, mxC = (1 << N) - 1;
    while (C <= mxC) {
        int s = 0;
        for (int i = 0; i < N; ++i)
            if (C & (1 << i))
                s += a[i];

        if (!sieve[s]) ans.emplace(s);

        int t = C | (C - 1);
        C = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(C) + 1));
    }

    if (ans.empty()) {cout << -1; return 0;}
    else for (int x : ans) cout << x << ' ';
    return 0;
}