#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int F(int n)
{
    int ret = 1;
    while (n) {
        ret *= n % 10;
        n /= 10;
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        if (n == 0) break;
        while (1) {
            cout << n << ' ';
            if (n < 10) break;
            n = F(n);
        }
        cout << '\n';
    }
    return 0;
}