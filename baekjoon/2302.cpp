#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int DP[41];
    DP[0] = DP[1] = 1, DP[2] = 2;
    for (int i = 3; i <= 40; ++i)
        DP[i] = DP[i - 1] + DP[i - 2];
    // DP[n] : n개 좌석에 사람들이 앉는 가짓수

    int n, m; cin >> n >> m;
    if (m == 0) cout << DP[n];
    else {
        // 만약 고정석의 위치가 a,b,c라면
        // 답은 [1,a-1]에 앉는 방법 * [a+1,b-1]에 앉는 방법 * ... * [b+1,n]에 앉는 방법이다
        int Ans = 1, Start = 0, End;
        while (m--) {
            cin >> End;
            Ans *= DP[End - Start - 1];
            Start = End;
        }
        Ans *= DP[n - Start];
        cout << Ans;
    }
    return 0;
}