#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int B;
        string s;
        cin >> B >> s;
        int sum = 0, len = s.size();
        loop(i, len)
            sum += s[i] - '0';
        cout << sum % (B - 1) << '\n';
    }
    return 0;
}