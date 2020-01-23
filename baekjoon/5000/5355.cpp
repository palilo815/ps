#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int t; cin >> t;
    double n;
    while (t--) {
        cin >> n;
        string s;
        getline(cin, s);
        loop(i, s.size()) {
            if (s[i] == '@') n *= 3;
            else if (s[i] == '%') n += 5;
            else if (s[i] == '#') n -= 7;
        }
        cout << fixed << setprecision(2) << n << '\n';
    }
    return 0;
}