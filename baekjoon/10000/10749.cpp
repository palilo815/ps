#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 2e3;

int id[mxN], dist[mxN];
bool conn[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> id[i];

    long long ans = 0;
    loop(_, N) {
        int k = -1;
        loop(i, N) if (!conn[i] && (k == -1 || dist[i] > dist[k]))
            k = i;

        ans += dist[k];
        conn[k] = true;

        loop(i, N) if (!conn[i] && (id[i] ^ id[k]) > dist[i])
            dist[i] = id[i] ^ id[k];
    }
    cout << ans;
    return 0;
}