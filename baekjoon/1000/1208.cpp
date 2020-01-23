#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll DP[8000001];
// 0을 4000000으로 표현하기로 한다.
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, S; cin >> N >> S;
    while (N--) {
        int x; cin >> x;
        if (x < 0)
            for (int i = -x;i <= 8000000;++i)
                DP[i + x] += DP[i];
        else
            for (int i = 8000000 - x; i >= 0;--i)
                DP[i + x] += DP[i];
        ++DP[x + 4000000];
    }
    cout << DP[S + 4000000];
    return 0;
}