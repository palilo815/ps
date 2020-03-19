#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_M = 100;

int need[max_M];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K; cin >> N >> M >> K;
    loop(i, M) {
        int mask = 0;
        loop(j, K) {
            int skill; cin >> skill;
            mask |= 1 << (skill - 1);
        }
        need[i] = mask;
    }

    int ans = 0;
    loop(i, 1 << (2 * N)) if (__builtin_popcount(i) == N) {
        int cnt = 0;
        loop(j, M) if ((need[j] & i) == need[j]) ++cnt;
        ans = max(ans, cnt);
    }
    cout << ans;
    return 0;
}