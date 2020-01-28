#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, a, b;
    string s;
    cin >> T;
    while (T--) {
        cin >> a >> b >> s;
        for (char c : s) {
            int code = (a * (c - 'A') + b) % 26;
            cout << (char)(code + 'A');
        }
        cout << '\n';
    }
    return 0;
}