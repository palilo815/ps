#include <bits/stdc++.h>
#define diff(x,y) min(abs(a[x]-a[y]),24-abs(a[x]-a[y]))
using namespace std;

const int mx = 1e3;

int a[mx + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);
    a[N] = a[0];

    int s1 = 0, s2 = 0;
    for (int i = 0; i < N; i += 2)
        s1 += diff(i, i + 1), s2 += diff(i + 1, i + 2);
    cout << min(s1, s2);
    return 0;
}