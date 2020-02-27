#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 100000;

int R[MAX], C[MAX];
int DP[MAX];

int solve(int arr[], int len) {
    if (len == 1) return arr[0];
    memset(DP, 0, sizeof(int) * len);
    DP[0] = arr[0], DP[1] = max(arr[0], arr[1]);
    for (int i = 2; i < len; ++i)
        DP[i] = max(DP[i - 1], DP[i - 2] + arr[i]);
    return DP[len - 1];
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col;
    while (cin >> row >> col) {
        if (row == 0) break;
        loop(i, row) {
            loop(j, col) cin >> C[j];
            R[i] = solve(C, col);
        }
        cout << solve(R, row) << '\n';
    }
    return 0;
}