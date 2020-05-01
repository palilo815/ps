#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int p[max_N * 2 + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string ori; cin >> ori;
    string s = "#";
    for (char c : ori) {
        s += c;
        s += '#';
    }

    int l = 0, r = -1, N = s.size();
    for (int i = 0; i < N; ++i) {
        int k;
        if (i > r) k = 0;
        else k = min(p[l + r - i], r - i);

        while (i - k > 0 && i + k < N - 1 && s[i - k - 1] == s[i + k + 1])
            ++k;

        p[i] = k;
        if (i + k > r)
            l = i - k, r = i + k;
    }
    cout << *max_element(p, p + N);
    return 0;
}