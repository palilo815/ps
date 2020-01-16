#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int fibo[2][2] = { 0,1,1,0 };
    int n, k; cin >> n >> k;
    for (int i = 3; i <= n; ++i) {
        fibo[i % 2][0] = fibo[0][0] + fibo[1][0];
        fibo[i % 2][1] = fibo[0][1] + fibo[1][1];
    }
    int A = fibo[n % 2][0], B = fibo[n % 2][1];
    for (int a = 1;; ++a) {
        int tteock = k - a * A;
        if (tteock % B == 0) {
            cout << a << '\n' << tteock / B;
            break;
        }
    }
    return 0;
}