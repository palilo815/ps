#include<bits/stdc++.h>
using namespace std;
int Cache[8][31];

// 켜진 비트 수 return
int NofB(int n)
{
    int ret = 0;
    while (n) { n = n & (n - 1); ++ret; }
    return ret;
}

// 현재 타일 상태는 mask, n줄을 더 채워야함.
int DP(int Mask, int n)
{
    // n==0 : 다 채운 경우
    // n==1 : 어차피 경우의 수는 하나
    if (n <= 1) return 1;
    int& ret = Cache[Mask][n];
    if (ret != -1) return ret;

    int num1 = NofB(Mask);
    // ㅁ : 타일, . : 빈 자리
    // 상 -> 하 방향으로 채운다.

    // .ㅁㅁ  ㅁ.ㅁ  ㅁㅁ.
    // 빈 공간에 세로 타일을 넣는 경우 한 가지.
    if (num1 == 2)
        ret = DP(Mask ^ 7, n - 1);
    // ..ㅁ  ㅁ..
    // 빈 공간을 가로 타일로 완전 채우는 경우
    // 또는 세로 타일 두 개를 넣는 경우
    // .ㅁ. 이 경우는 세로타일 두 개 밖에 안됨.
    else if (num1 == 1) {
        if (Mask == 2) ret = DP(5, n - 1);
        else ret = DP(0, n - 1) + DP(Mask ^ 7, n - 1);
    }
    // ...
    // 가로 타일을 왼쪽 또는 오른쪽에 놓는 경우 두 가지
    // 세로 타일 세 개를 놓는 경우
    else
        ret = DP(3, n) + DP(6, n) + DP(0, n - 2);
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(Cache, -1, sizeof(Cache));
    int n; cin >> n;
    if (n % 2) cout << 0;
    else cout << DP(0, n);
    return 0;
}