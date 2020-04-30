#include <bits/stdc++.h>
using namespace std;

const int max_N = 2000;

int w[max_N];
int head[max_N];
int tail[max_N];

// head[i] : i번 기차가 맨 앞
// tail[i] : i번 기차가 맨 뒤
// ans = h + t - 1

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> w[i];

    for (int i = N - 1; i >= 0; --i) {
        head[i] = tail[i] = 1;
        for (int j = i + 1; j < N; ++j) {
            if (w[i] > w[j]) head[i] = max(head[i], head[j] + 1);
            else tail[i] = max(tail[i], tail[j] + 1);
        }
    }

    int ans = (N == 0);
    for (int i = 0; i < N; ++i)
        ans = max(ans, head[i] + tail[i]);
    cout << ans - 1;
    return 0;
}