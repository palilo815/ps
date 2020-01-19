#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n, s, t;
    while (cin >> n) {
        if (n == -1) break;
        int Time = 0, Dst = 0;
        while (n--) {
            cin >> s >> t;
            Dst += (t - Time) * s;
            Time = t;
        }
        cout << Dst << " miles\n";
    }
    return 0;
}