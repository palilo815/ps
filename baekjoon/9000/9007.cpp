#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000;

int arr[2][max_N];
int A[max_N * max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int K, N; cin >> K >> N;
        loop(i, 2) loop(j, N) cin >> arr[i][j];
        int pos = 0, len = N * N;
        loop(i, N) loop(j, N) A[pos++] = arr[0][i] + arr[1][j];
        sort(A, A + len);

        int ans = INT_MAX;
        loop(i, 2) loop(j, N) cin >> arr[i][j];
        loop(i, N) loop(j, N) {
            int b = arr[0][i] + arr[1][j];
            auto it = lower_bound(A, A + len, K - b);
            if (it != A + len) {
                int tmp = b + *it;
                if (abs(tmp - K) < abs(ans - K) || (abs(tmp - K) == abs(ans - K) && tmp < ans))
                    ans = tmp;
            }
            if (it != A) {
                int tmp = b + *(--it);
                if (abs(tmp - K) < abs(ans - K) || (abs(tmp - K) == abs(ans - K) && tmp < ans))
                    ans = tmp;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}