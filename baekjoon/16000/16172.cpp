#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string s, k; cin >> s >> k;
    s.erase(remove_if(s.begin(), s.end(), [&](char c) {
        return '0' <= c && c <= '9';
    }), s.end());

    int M = k.size();
    vector<int> lps(M);
    for (int i = 1, j = 0; i < M; ++i) {
        while (j && k[i] ^ k[j]) j = lps[j - 1];
        if (k[i] == k[j]) lps[i] = ++j;
    }

    int N = s.size();
    for (int i = 0, j = 0; i < N; ++i) {
        while (j && s[i] ^ k[j]) j = lps[j - 1];
        if (s[i] == k[j] && ++j == M) {
            cout << 1;
            return 0;
        }
    }
    cout << 0;
    return 0;
}