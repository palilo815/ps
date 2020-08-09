#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    int s = 0, odd = 0;
    for (int h; N--;) {
        cin >> h;
        s += h;
        if (h & 1) ++odd;
    }
    cout << ((s % 3 == 0 && odd <= s / 3) ? "YES" : "NO");
    return 0;
}