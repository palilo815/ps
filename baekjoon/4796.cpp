#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int L, P, V, T = 0;
    while (1) {
        cin >> L >> P >> V;
        if (L + P + V == 0) break;
        int Ans = (V / P) * L + min(V % P, L);
        cout << "Case " << ++T << ": " << Ans << '\n';
    }
    return 0;
}