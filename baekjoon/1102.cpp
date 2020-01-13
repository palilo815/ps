#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define max_N 16

int n, arr[max_N][max_N];
int Cache[(1 << max_N) - 1][max_N - 1];
int FindMin(int mask, int next)
{
    int ret = INT32_MAX;
    loop(i, n)
        if ((1 << i) & mask)
            ret = min(ret, arr[i][next]);
    return ret;
}
int DP(int mask, int num)	//mask상태에서 num개의 발전소를 더 키기 위한 최솟값
{
    if (num <= 0) return 0;
    int& ret = Cache[mask][num - 1];
    if (ret != -1) return ret;
    int tmp = INT32_MAX / 2;
    loop(i, n)
        if (!((1 << i) & mask)) {
            int cost = FindMin(mask, i);
            tmp = min(tmp, cost + DP(mask + (1 << i), num - 1));
        }
    return ret = tmp;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(Cache, -1, sizeof(Cache));
    cin >> n;
    loop(i, n) loop(j, n) cin >> arr[i][j];

    int mask = 0, num = 0, P;
    string s; cin >> s;
    reverse(s.begin(), s.end()); // mask 계산 편하도록
    loop(i, n) {
        mask = mask << 1;
        if (s[i] == 'Y') ++mask, ++num;
    }
    cin >> P;

    // P-num개의 발전소를 켜야한다.
    if (mask || P - num == 0) cout << DP(mask, P - num);
    // 발전소는 다 꺼져있는데, 추가로 발전소를 켜야 할 경우 불가능
    else cout << -1;
    return 0;
}