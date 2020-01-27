#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, a[5];
    cin >> T;
    loop(t, T) {
        loop(i, 5) cin >> a[i];
        sort(a, a + 5);
        cout << "Case #" << t + 1 << ": " << a[4] << '\n';
    }
    return 0;
}