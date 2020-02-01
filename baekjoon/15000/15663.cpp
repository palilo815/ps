#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 8;

bool selected[max_N];
int num[max_N];
vector<int> vt;
void solve(int N, int M)
{
    if (M == 0) {
        for (int i : vt) cout << num[i] << ' ';
        cout << '\n';
        return;
    }
    int prev_num = 0;
    loop(i, N)
        if (!selected[i] && num[i] != prev_num) {
            prev_num = num[i];
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

    // N개의 자연수 중에서 M개를 고른 수열
    // 중복되는 수열을 여러 번 출력하면 안된다.

    int N, M; cin >> N >> M;
    loop(i, N) cin >> num[i];
    sort(num, num + N);
    solve(N, M);
    return 0;
}