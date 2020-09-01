#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int H[mxN], P[mxN], S[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        char c; cin >> c;
        if (c == 'H') ++H[i];
        else if (c == 'P') ++P[i];
        else ++S[i];
    }

    partial_sum(H, H + N, H);
    partial_sum(P, P + N, P);
    partial_sum(S, S + N, S);

    int ans = 0;
    for (int i = 0; i < N; ++i)
        ans = max(ans, max({H[i], P[i], S[i]}) + max({H[N - 1] - H[i], P[N - 1] - P[i], S[N - 1] - S[i]}));
    cout << ans;
    return 0;
}