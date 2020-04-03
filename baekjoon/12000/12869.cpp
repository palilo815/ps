#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;

const int dmg[6][3] = { 9,3,1,9,1,3,3,9,1,3,1,9,1,9,3,1,3,9 };

bool visited[69][69][69];

int main() {
    int N; cin >> N;
    vector<int> scv(3);
    for (int i = 0; i < N; ++i) cin >> scv[i];
    sort(scv.begin(), scv.end(), greater<int>());

    queue<tup> q;
    q.emplace(0, 0, 0), q.emplace(-1, -1, -1);

    int ans = 0;
    while (1) {
        auto [a, b, c] = q.front(); q.pop();
        if (a == -1) {
            ++ans; q.emplace(-1, -1, -1);
            continue;
        }
        if (a >= scv[0] && b >= scv[1] && c >= scv[2]) break;

        for (int i = 0; i < 6; ++i) {
            int A = a + dmg[i][0], B = b + dmg[i][1], C = c + dmg[i][2];
            if (A < B) swap(A, B);
            if (B < C) swap(B, C);
            if (A < B) swap(A, B);
            if (A >= 69) continue;
            if (!visited[A][B][C]) {
                visited[A][B][C] = true;
                q.emplace(A, B, C);
            }
        }
    }
    cout << ans;
    return 0;
}