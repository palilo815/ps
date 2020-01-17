#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cache[2][101][101];	//A로 시작 B자리수 C번 인접 1등장
int DP(int start, int len, int count)
{
    if (len == 0) {
        // 아직 세야할 count가 남았거나
        // start == 1이어서 이미 앞에서 개수를 샌 경우
        if (count || start == 1) return 0;
        // count개를 전부 세었고, 새로운 1이 등장한 경우
        else return 1;
    }
    int& ret = cache[start][len][count];
    if (ret != -1) return ret;

    if (start == 0)
        ret = DP(0, len - 1, count) + DP(1, len - 1, count);
    else {
        ret = DP(0, len - 1, count);
        if (count)
            ret += DP(1, len - 1, count - 1);
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(cache, -1, sizeof(cache));
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        cout << DP(0, n, k) + DP(1, n, k) << '\n';
    }
    return 0;
}