#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e3;

int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int W, N; cin >> W >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    unordered_set<int> st;
    for (int i = 0; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j)
            if (st.count(W - a[i] - a[j])) {
                cout << "YES";
                return 0;
            }
        for (int j = 0; j < i; ++j)
            st.insert(a[i] + a[j]);
    }
    cout << "NO";
    return 0;
}