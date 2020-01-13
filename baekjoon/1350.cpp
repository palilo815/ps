#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

ll file[1000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> file[i];
    ll Div; cin >> Div;
    ll Ans = 0;
    loop(i, n) {
        if (file[i]) {
            // tmp : i번 파일이 사용하는 용량
            ll tmp = file[i] / Div;
            tmp *= Div;
            if (tmp < file[i]) tmp += Div;
            Ans += tmp;
        }
    }
    cout << Ans;
    return 0;
}