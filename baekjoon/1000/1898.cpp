#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 5e4;

int a[mxN], idx[mxN + 1];
bool used[mxN + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i];
    loop(i, N) idx[a[i]] = i;

    used[0] = true;
    loop(i, N) if (!used[a[i]] && !used[a[i] - 1] && idx[a[i]] < idx[a[i] - 1]) {
        used[a[i]] = used[a[i] - 1] = true;
        swap(a[i], a[idx[a[i] - 1]]);
    }
    loop(i, N) cout << a[i] << '\n';
    return 0;
}