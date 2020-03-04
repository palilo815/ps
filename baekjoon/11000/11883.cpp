#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000000;

// cache[n] : 자리수의 합이 n인 가장 작은 생일수의 가장 낮은 자리수에 써있는 숫자.
int len[max_N + 6];
int cache[max_N + 6];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    fill(len + 1, len + max_N + 6, INT_MAX);
    cache[0] = -1;

    for (int i = 0; i < max_N - 2; ++i) if (cache[i]) {
        if (len[i + 8] > len[i] + 1) {
            len[i + 8] = len[i] + 1;
            cache[i + 8] = 8;
        }
        if (len[i + 5] > len[i] + 1) {
            len[i + 5] = len[i] + 1;
            cache[i + 5] = 5;
        }
        if (len[i + 3] > len[i] + 1) {
            len[i + 3] = len[i] + 1;
            cache[i + 3] = 3;
        }
    }
    vector<int> ans;

    int T; cin >> T;
    while (T--) {
        ans.clear();
        int N; cin >> N;
        if (!cache[N]) { cout << "-1\n"; continue; }
        while (N) {
            ans.push_back(cache[N]);
            N -= cache[N];
        }
        for (auto it = ans.rbegin(); it != ans.rend(); ++it)
            cout << *it;
        cout << '\n';
    }
    return 0;
}