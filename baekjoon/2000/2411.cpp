#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int MAX = 100;

bool wall[MAX + 1][MAX + 1];
int DP[MAX + 2][MAX + 2];
bool invalid;

auto cmp = [](const p& a, const p& b) {
    int A = a.first + a.second;
    int B = b.first + b.second;
    if (A == B) invalid = true;
    return A < B;
};
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, A, B;
    cin >> row >> col >> A >> B;

    vector<p> item(A);
    for (int i = 0; i < A; ++i)
        cin >> item[i].first >> item[i].second;

    while (B--) {
        int r, c; cin >> r >> c;
        wall[r][c] = true;
    }

    sort(item.begin(), item.end(), cmp);
    if (invalid) { cout << 0; return 0; }

    int sr = 1, sc = 1, ans = 1;
    item.emplace_back(row, col);
    for (auto [dr, dc] : item) {
        memset(DP, 0, sizeof(DP));
        DP[sr][sc] = 1;
        for (int r = sr; r <= dr; ++r)
            for (int c = sc; c <= dc; ++c) {
                if (wall[r][c]) continue;
                DP[r][c + 1] += DP[r][c];
                DP[r + 1][c] += DP[r][c];
            }
        ans *= DP[dr][dc];
        sr = dr, sc = dc;
    }
    cout << ans;
    return 0;
}