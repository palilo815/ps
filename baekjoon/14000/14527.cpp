#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

p cow[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> cow[i].second >> cow[i].first;
    sort(cow, cow + N);

    int i = 0, j = N - 1, ans = 0;
    while (i <= j) {
        ans = max(ans, cow[i].first + cow[j].first);
        int x = min(cow[i].second, cow[j].second);
        cow[i].second -= x;
        cow[j].second -= x;
        if (cow[i].second <= 0) ++i;
        if (cow[j].second <= 0) --j;
    }
    cout << ans;
    return 0;
}