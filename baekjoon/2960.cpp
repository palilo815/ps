#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool sieve[1001];
int Eratos(int N, int k)
{
    for(int i=2; i<=N; ++i)
        if (!sieve[i])
            for (int j = i; j <= N; j += i)
                if (!sieve[j]) {
                    if (--k == 0) return j;
                    sieve[j] = true;
                }
    return 0;
}
int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N, k; cin >> N >> k;
    cout << Eratos(N, k);
    return 0;
}