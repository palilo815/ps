#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (getline(cin, s)) {
        if (s == "#") break;
        int L = s.size(), sum = 0;
        loop(i, L) {
            if (s[i] == ' ') continue;
            sum += (i + 1) * (s[i] - 64);
        }
        cout << sum << '\n';
    }
    return 0;
}