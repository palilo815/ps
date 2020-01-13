#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool sieve[100001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    sieve[0] = sieve[1] = true;
    int a, b, ans = 0;
    cin >> a >> b;
    vector<int> prime;

    // 에라토스테네스의 체로 소수를 구해서 prime vector에 넣는다.
    for (int i = 2; i <= b; ++i)
        if (!sieve[i]) {
            prime.push_back(i);
            for (int j = i * 2; j <= b; j += i)
                sieve[j] = true;
        }


    for (int N = a; N <= b; ++N) {
        // N이 소수면 패스
        if (!sieve[N]) continue;
        int num = N, cnt = 0, i = 0;
        while (num != 1) {
            while (num % prime[i] == 0) {
                num /= prime[i];
                ++cnt;
            }
            ++i;
        }
        if (!sieve[cnt]) ++ans;
    }
    cout << ans;
    return 0;
}