#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0; i<n; ++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) {
        loop(j, n) cout << '*';
        cout << '\n';
    }
    return 0;
}