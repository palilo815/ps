#include <iostream>
using namespace std;
#define MOD 10007

int DP[1001];
int main()
{
    int N; cin >> N;

    // basis
    DP[1] = 1; // : |
    DP[2] = 3; // : ||, =, ㅁ

    // 2xi 타일링은
    // i-1에서 |를 추가하거나, i-2에서 = 또는 ㅁ을 추가하면 된다.
    for (int i = 3;i <= N;++i)
        DP[i] = (DP[i - 1] + 2 * DP[i - 2]) % MOD;

    cout << DP[N];
    return 0;
}