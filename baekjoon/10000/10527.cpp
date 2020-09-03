#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    unordered_map<string, int> A, B;

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        ++A[s];
    }
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        ++B[s];
    }

    int ans = 0;
    for (auto& [s, cnt] : A)
        ans += min(cnt, B[s]);
    cout << ans;
    return 0;
}