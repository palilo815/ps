#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, t;
    cin >> t;
    while (t--) {
        cin >> n;
        loop(i, n) {
            loop(j, n)
                if (i == 0 || i == n - 1 || j == 0 || j == n - 1) cout << '#';
                else cout << 'J';
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}