#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 300;

int N, M;
int arr[max_N];

int solve(int m) {
    int ret = 1, sum = 0;
    loop(i, N) {
        if (sum + arr[i] > m) ++ret, sum = 0;
        sum += arr[i];
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    int l = 0, r = 0;
    loop(i, N) {
        cin >> arr[i];
        l = max(l, arr[i]);
        r += arr[i];
    }

    while (l < r) {
        int m = (l + r) >> 1;
        solve(m) > M ? (l = m + 1) : (r = m);
    }

    vector<int> ans(M);
    int cnt = 0, sum = 0, it = 0;
    loop(i, N) {
        if (sum + arr[i] > l) {
            ans[it++] = cnt;
            cnt = sum = 0;
        }
        ++cnt, sum += arr[i];
    }
    ans[it++] = cnt;

    for (; it < M; ++it) {
        ++ans[it];
        loop(j, M) if (ans[j] > 1) {
            --ans[j];
            break;
        }
    }

    cout << l << '\n';
    for (int x : ans) cout << x << ' ';
    return 0;
}