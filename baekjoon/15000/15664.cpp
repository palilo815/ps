#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 8;

int num[max_N];
vector<int> vt;
void solve(int N, int M, int prev_idx)
{
    if (M == 0) {
        for (int i : vt) cout << num[i] << ' ';
        cout << '\n';
        return;
    }
    int prev_num = 0;
    for (int i = prev_idx + 1; i < N - M + 1; ++i)
        if (num[i] != prev_num) {
            prev_num = num[i];
            vt.push_back(i);
            solve(N, M - 1, i);
            vt.pop_back();
        }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // N개의 자연수 중에서 M개를 고른 수열
    // 중복되는 수열을 여러 번 출력하면 안된다.
    // 고른 수열은 비내림차순이어야 한다.

    int N, M; cin >> N >> M;
    loop(i, N) cin >> num[i];
    sort(num, num + N);
    solve(N, M, -1);
    return 0;
}