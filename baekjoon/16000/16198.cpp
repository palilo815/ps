#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 10;

int N, DP[1 << max_N], arr[max_N];

// 남아있는 구슬이 balls 형태일 때, 여기서 id번 구슬을 제거한다.
void get_energy(int balls, int id) {
    // 만약 balls에 id가 없으면 return
    int mask = 1 << id;
    if (!(balls & mask)) return;

    // id를 기준으로, 왼쪽에 있는 구슬과 오른쪽에 있는 구슬을 찾는다.
    int L = -1, R = -1;
    for (int i = id + 1; i < N;++i)
        if ((1 << i) & balls) {
            L = i; break;
        }
    for (int i = id - 1;i >= 0;--i)
        if ((1 << i) & balls) {
            R = i; break;
        }

    // L, R중 하나라도 없으면 return
    if (L == -1 || R == -1) return;

    // id를 제거하고, arr[L]*arr[R]만큼의 에너지를 얻는다.
    int& ret = DP[balls ^ mask];
    ret = max(ret, DP[balls] + arr[L] * arr[R]);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    loop(i, N) cin >> arr[i];
    loop(t, N - 2) loop(i, N) {
        loop(j, 1 << N)
            get_energy(j, i);
    }
    int ans = 0;
    loop(i, 1 << N) ans = max(ans, DP[i]);
    cout << ans;
    return 0;
}