#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int pos = 0;
        while (n) {
            if (n % 2) cout << pos << ' ';
            n /= 2; ++pos;
        }
        cout << '\n';
    }
    return 0;
}