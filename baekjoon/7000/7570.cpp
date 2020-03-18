#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000000;

int con[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int h; cin >> h;
        if (con[h - 1]) {
            con[h] = con[h - 1] + 1;
            ans = max(ans, con[h]);
        }
        else con[h] = 1;
    }
    cout << N - ans;
    return 0;
}