#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100;

p paper[max_N];
int DP[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        int w, h; cin >> w >> h;
        if (w < h) swap(w, h);
        paper[i] = { w,h };
    }
    sort(paper, paper + N, greater<p>());

    for (int i = 0; i < N; ++i) {
        if (!DP[i]) DP[i] = 1;
        for (int j = i + 1; j < N; ++j)
            if (paper[i].second >= paper[j].second)
                DP[j] = max(DP[j], DP[i] + 1);
    }

    int ans = 0;
    for (int i = 0; i < N; ++i)
        ans = max(ans, DP[i]);
    cout << ans;
    return 0;
}