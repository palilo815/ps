#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000000;
int A[max_N];
int B[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        loop(i, N) cin >> A[i];
        loop(i, M) cin >> B[i];
        sort(B, B + M);

        long long ans = 0;
        loop(i, N) {
            int x = A[i], tmp = INT_MAX;
            auto it = lower_bound(B, B + M, x);
            if (it != B + M) tmp = *it;
            if (it != B) {
                --it;
                tmp = (tmp - x >= x - *it ? *it : tmp);
            }
            ans += tmp;
        }
        cout << ans << '\n';
    }
    return 0;
}