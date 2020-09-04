#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

const int mxN = 2e4;

int chicken[mxN];
p cow[mxN + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int C, N; cin >> C >> N;
    loop(i, C) cin >> chicken[i];
    loop(i, N) cin >> cow[i].first >> cow[i].second;

    sort(chicken, chicken + C);
    sort(cow, cow + N);
    cow[N].first = INT_MAX;

    priority_queue<int> pq;
    int ans = 0;

    for (int i = 0, j = 0; i < C; ++i) {
        while (cow[j].first <= chicken[i])
            pq.emplace(-cow[j++].second);
        while (!pq.empty() && chicken[i] > -pq.top())
            pq.pop();

        if (!pq.empty() && chicken[i] <= -pq.top()) {
            ++ans;
            pq.pop();
        }
    }
    cout << ans;
    return 0;
}