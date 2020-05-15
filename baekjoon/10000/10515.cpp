#include <bits/stdc++.h>
using namespace std;

const int max_N = 102;

int stt[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        int D, K, N; cin >> D >> K >> N;
        for (int i = 1; i <= N; ++i) cin >> stt[i];
        stt[++N] = D;

        int impossible = 0;
        for(int i=1; i<=N; ++i)
            if (stt[i] - stt[i - 1] > K) {
                impossible = 1;
                break;
            }
        if(impossible){
            cout << "Case #" << t << ": out of petrol\n";
            continue;
        }

        vector<int> path;
        int d = 0;
        for (int i = 0; i < N; ++i) {
            if (d + stt[i + 1] - stt[i] > K) {
                d = 0;
                path.emplace_back(i);
            }
            d += stt[i + 1] - stt[i];
        }

        cout << "Case #" << t << ':';
        for (int x : path) cout << ' ' << stt[x];
        cout << '\n';
    }
    return 0;
}