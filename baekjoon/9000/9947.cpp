#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s1, s2;
    char a, b;
    while (cin >> s1 >> s2) {
        if (s1 == "#") break;
        int n; cin >> n;
        int sum1 = 0, sum2 = 0;
        while (n--) {
            cin >> a >> b;
            if (a == b) ++sum1;
            else ++sum2;
        }
        cout << s1 << ' ' << sum1 << ' ' << s2 << ' ' << sum2 << '\n';
    }
    return 0;
}