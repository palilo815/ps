#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        int s, n;
        cin >> s >> n;
        while (n--) {
            int a, b;
            cin >> a >> b;
            s += a * b;
        }
        cout << s << '\n';
    }
    return 0;
}