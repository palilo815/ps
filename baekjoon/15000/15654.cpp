#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 8;

int num[max_N];
bool selected[max_N];
vector<int> vt;
void solve(int N, int M)
{
    if (M == 0) {
        for (int i : vt) cout << num[i] << ' ';
        cout << '\n';
        return;
    }
    loop(i, N)
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

    // N개의 자연수 중에서 M개를 고른 수열

    int N, M; cin >> N >> M;
    loop(i, N) cin >> num[i];
    sort(num, num + N);
    solve(N, M);
    return 0;
}