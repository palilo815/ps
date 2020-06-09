#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 10001;

int arr[max_N];
int DP[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> arr[i];

    DP[0] = 0;
    DP[1] = arr[1];
    DP[2] = arr[1] + arr[2];

    for (int i = 3; i <= N; ++i)
        DP[i] = max({DP[i - 3] + arr[i - 1] + arr[i],
                     DP[i - 2] + arr[i],
                     DP[i - 1]
                    });
    cout << DP[N];
    return 0;
}