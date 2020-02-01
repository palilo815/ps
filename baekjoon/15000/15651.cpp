#include <bits/stdc++.h>
using namespace std;

vector<int> vt;
void solve(int N, int M)
{
    if (M == 0) {
        for (int x : vt) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int i = 1; i <= N; ++i) {
        vt.push_back(i);
        solve(N, M - 1);
        vt.pop_back();
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 1부터 N까지 자연수 중에서 M개를 고른 수열
    // 같은 수를 여러 번 골라도 된다.

    int N, M; cin >> N >> M;
    solve(N, M);
    return 0;
}