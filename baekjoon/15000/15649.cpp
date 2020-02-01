#include <bits/stdc++.h>
using namespace std;
const int max_N = 8;

bool selected[max_N + 1];
vector<int> vt;
void solve(int N, int M)
{
    if (M == 0) {
        for (int x : vt) cout << x << ' ';
        cout << '\n';
        return;
    }
    for (int i = 1;i <= N;++i)
        if (!selected[i]) {
            selected[i] = true;
            vt.push_back(i);
            solve(N, M - 1);
            selected[i] = false;
            vt.pop_back();
        }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
    int N, M; cin >> N >> M;
    solve(N, M);
    return 0;
}