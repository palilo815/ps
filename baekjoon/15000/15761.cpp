#include <bits/stdc++.h>
using namespace std;

const int mx = 1e5;

int a[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    sort(a, a + N, greater<int>());

    int i = 0;
    while (i < N && a[i] >= i) ++i;
    cout << i;
    return 0;
}