#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> p;

const int max_N = 301;

p A[max_N];
int DP[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> A[i].first >> A[i].second;
    sort(A + 1, A + N + 1);

    memset(DP + 1, 0x3f, sizeof(int) * N);
    for (int i = 1; i <= N; ++i) {
        DP[i] = min(DP[i], DP[i - 1] + 1);
        auto [x, h] = A[i];
        ll L = x - h, R = x + h;

        for (int j = i - 1; j; --j) {
            if (L <= A[j].first)
                L = min(L, A[j].first - A[j].second),
                DP[i] = min(DP[i], DP[j - 1] + 1);
            else break;
        }
        for (int j = i + 1; j <= N; ++j) {
            if (A[j].first <= R)
                R = max(R, A[j].first + A[j].second),
                DP[j] = min(DP[j], DP[i - 1] + 1);
            else break;
        }
    }
    cout << DP[N];
    return 0;
}