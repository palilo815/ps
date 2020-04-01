#include <bits/stdc++.h>
using namespace std;

int A[26], B[26];
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    string key; cin >> key;

    for (char c : key) ++A[c - 'A'];
    int ans = 0;
    while (--N) {
        memset(B, 0, sizeof(B));
        string s; cin >> s;
        for (char c : s) ++B[c - 'A'];

        int gap = 0;
        for (int i = 0; i < 26; ++i)
            gap += abs(A[i] - B[i]);
        if (gap <= 2 && abs((int)s.size() - (int)key.size()) <= 1) ++ans;
    }
    cout << ans;
    return 0;
}