#include<iostream>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define MOD 10007

// 길이가 A고, B로 시작하는 오르막 수
int DP[1001][10];
int main()
{
    int N; cin >> N;

    // basis : 한 자리 오르막수는 전부 한 가지
    loop(i, 10) DP[i][1] = 1;

    // i자리이며 j로 시작하는 오르막 수는
    // i-1자이며 j 이상의 숫자로 시작하는 오르막 수 앞에 j를 붙이면 된다.
    for (int i = 2; i <= N; ++i)
        loop(j, 10) {
            int sum = 0;
            for (int k = j;k < 10;++k)
                sum += DP[k][i - 1];
            DP[j][i] = sum % MOD;
        }

    // N자리 오르막 수를 전부 더해서 출력
    int ans = 0;
    loop(i, 10) ans += DP[i][N];
    cout << ans % MOD;
    return 0;
}