#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int P[8], Sum = 0;
    loop(i, 8) {
        cin >> P[i];
        Sum += P[i];
    }
    int Ans = 0;
    loop(i, 4) {
        int tmp = 0;
        loop(j, 4) tmp += P[i + j];
        tmp = max(tmp, Sum - tmp);
        Ans = max(Ans, tmp);
    }
    cout << Ans;
    return 0;
}