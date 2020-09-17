#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s;
    cin >> s;
    int N = s.size();

    unordered_set<string> st;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j <= N; ++j)
            st.emplace(s.substr(i, j - i));
    cout << st.size();
    return 0;
}