#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b, c, N;
    cin >> a >> b >> c >> N;
    for (int i = 0; a * i <= N; ++i) {
        int rem = N - a * i;
        for (int j = 0; b * j <= rem; ++j) {
            int rem2 = rem - b * j;
            if (rem2 % c == 0) {
                cout << 1;
                return 0;
            }
        }
    }
    cout << 0;
    return 0;
}