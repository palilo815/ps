#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;

string a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
        reverse(a[i].begin(), a[i].end());
    }

    sort(a, a + N);

    for (int i = 0; i < N; ++i)
        cout << a[i] << '\n';
    return 0;
}