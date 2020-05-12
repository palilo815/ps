#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

p arr[max_N];
double DP[max_N];

double dist(int u, int v) {
    double dx = arr[u].first - arr[v].first;
    double dy = arr[u].second - arr[v].second;
    return sqrt(dx * dx + dy * dy);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> arr[i].first >> arr[i].second;
    sort(arr, arr + N);

    loop(i, N) {
        auto [x, y] = arr[i];
        for (auto nxt = upper_bound(arr + i + 1, arr + N, make_pair(x, INT_MAX)) - arr; nxt < N; ++nxt)
            DP[nxt] = max(DP[nxt], DP[i] + dist(i, nxt));
    }

    cout << fixed << setprecision(9)
         << *max_element(DP, DP + N);
    return 0;
}