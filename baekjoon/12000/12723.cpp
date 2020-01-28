#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 8;

int arr[2][max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N; cin >> N;
        loop(i, 2) loop(j, N) cin >> arr[i][j];
        sort(arr[0], arr[0] + N);
        sort(arr[1], arr[1] + N, greater<int>());
        int ans = 0;
        loop(i, N) ans += arr[0][i] * arr[1][i];
        cout << "Case #" << t << ": " << ans << '\n';
    }
    return 0;
}