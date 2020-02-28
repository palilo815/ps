#include<bits/stdc++.h>
using namespace std;

const int max_N = 30;
int cache[max_N][1 << 3];

// 현재 타일 상태는 mask, n줄을 더 채워야함.
int DP(int n, int mask)
{
    // n==0 : 다 채운 경우
    // n==1 : 어차피 경우의 수는 하나
    if (n <= 0) return 1;
    int& ret = cache[n][mask];
    if (ret != -1) return ret;

    int num = __builtin_popcount(mask);
    // ㅁ : 타일, . : 빈 자리
    // 상 -> 하 방향으로 채운다.

    // .ㅁㅁ  ㅁ.ㅁ  ㅁㅁ.
    // 빈 공간에 세로 타일을 넣는 경우 한 가지.
    if (num == 2) ret = DP(n - 1, mask ^ 7);
    // ..ㅁ  ㅁ..
    // 빈 공간을 가로 타일로 완전 채우는 경우
    // 또는 세로 타일 두 개를 넣는 경우
    // .ㅁ. 이 경우는 세로타일 두 개 밖에 안됨.
    else if (num == 1) {
        if (mask == 2) ret = DP(n - 1, 5);
        else ret = DP(n - 1, 0) + DP(n - 1, mask ^ 7);
    }
    // ...
    // 가로 타일을 왼쪽 또는 오른쪽에 놓는 경우 두 가지
    // 세로 타일 세 개를 놓는 경우
    else ret = DP(n, 3) + DP(n, 6) + DP(n - 2, 0);
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(cache, -1, sizeof(cache));
    int n; cin >> n;
    if (n % 2) cout << 0;
    else cout << DP(n - 1, 0);
    return 0;
}