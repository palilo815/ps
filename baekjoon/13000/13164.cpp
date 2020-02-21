#include <bits/stdc++.h>
using namespace std;

const int max_N = 300000;

int gap[max_N - 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    int a, b;
    cin >> a;
    for (int i = 0; i < N - 1; ++i) {
        cin >> b;
        gap[i] = b - a;
        a = b;
    }
    sort(gap, gap + N - 1);
    int ans = 0;
    for (int i = 0; i < N - K; ++i)
        ans += gap[i];
    cout << ans;
    return 0;
}