#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    string s;
    while (t--) {
        cin >> s;
        int pos = 0, len = s.size();
        while (pos < len) {
            char c = s[pos];
            int end = pos;
            while (s[end] == c) {
                ++end;
                if (end == len) break;
            }
            cout << end - pos << c;
            pos = end;
        }
        cout << '\n';
    }
    return 0;
}