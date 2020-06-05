#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 2000;

int arr[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> arr[i];
    arr[N] = INT_MAX;
    sort(arr, arr + N);

    int ans = 0;
    loop(i, N) {
        int good = 0;
        loop(j, N) if (i != j) {
            int v = arr[i] - arr[j];
            int k = lower_bound(arr, arr + N, v) - arr;
            while (k == i || k == j) ++k;
            if (arr[k] == v) {
                good = 1;
                break;
            }
        }
        ans += good;
    }
    cout << ans;
    return 0;
}