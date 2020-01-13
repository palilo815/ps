#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

ll Sqr[4][2], Vt[4][2];
// a점과 b점 사이의 거리
ll Dst(int a, int b)
{
    ll dy = Sqr[a][0] - Sqr[b][0], dx = Sqr[a][1] - Sqr[b][1];
    return dy * dy + dx * dx;
}
// 내적
ll MulVt(int a, int b)
{
    return Vt[a][0] * Vt[b][0] + Vt[a][1] * Vt[b][1];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T-- > 0) {
        loop(i, 4) loop(j, 2) cin >> Sqr[i][j];
        ll D1 = Dst(0, 1), D2 = Dst(0, 2), D3, D4;
        // 0~3번 점의 상대적 위치가
        // 0 1
        // 3 2 가 되도록 만든다.
        if (D1 == D2)
            swap(Sqr[2], Sqr[3]);
        else if (D1 > D2)
            swap(Sqr[1], Sqr[2]);

        D1 = Dst(0, 1), D2 = Dst(1, 2), D3 = Dst(2, 3), D4 = Dst(3, 0);
        // 이제 위의 모양이 되었으므로
        // 각 변의 길이는 0~1, 1~2, 2~3, 3~0이다.

        // 변이 하나라도 다르면 꽝
        if (!(D1 == D2 && D2 == D3 && D3 == D4)) { cout << "0\n"; continue; }
        loop(i, 4) loop(j, 2)
            Vt[i][j] = Sqr[(i + 1) % 4][j] - Sqr[i][j];
        D1 = MulVt(0, 1), D2 = MulVt(1, 2), D3 = MulVt(2, 3), D4 = MulVt(3, 0);
        // 마름모가 될 시 꽝
        if (D1 || D2 || D3 || D4) { cout << "0\n"; continue; }
        cout << "1\n";
    }
    return 0;
}