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
        int Len = s.length() - 1;
        int n = s[Len] - 'A';
        loop(i, Len) {
            char c = s[i];
            if (c >= 'a' && c <= 'z') {
                c -= n;
                if (c < 'a') c += 26;
            }
            else if (c >= 'A' && c <= 'Z') {
                c -= n;
                if (c < 'A') c += 26;
            }
            cout << c;
        }
        cout << '\n';
    }
    return 0;
}