#include <bits/stdc++.h>
using namespace std;

vector<int> vt;
void solve(int N, int M, int prev_num)
{
    if (M == 0) {
        for (int x : vt) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int i = prev_num + 1; i <= N - M + 1; ++i) {
        vt.push_back(i);
        solve(N, M - 1, i);
        vt.pop_back();
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
    // 고른 수열은 오름차순이어야 한다.

    int N, M; cin >> N >> M;
    solve(N, M, 0);
    return 0;
}