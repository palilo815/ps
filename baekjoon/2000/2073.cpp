// ** choyi0521 풀이 **
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_D = 100000;
const int max_N = 350;

bool DP[max_D + 1];
p pipe[max_N];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int D, N; cin >> D >> N;
    for (int i = 0; i < N; ++i)
        cin >> pipe[i].second >> pipe[i].first;
    sort(pipe, pipe + N, greater<p>());

    DP[0] = true;
    int ans;
    for (int i = 0; i < N; ++i) {
        auto [capacity, len] = pipe[i];
        for (int j = D; j >= len; --j)
            DP[j] |= DP[j - len];
        if (DP[D]) {
            ans = capacity;
            break;
        }
    }
    cout << ans;
    return 0;
}