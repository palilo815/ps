#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    string s;
    cin >> n >> s;
    int L = 0, R = n - 1;
    while (L < R) {
        if (s[L] != s[R]) {
            if (s[L] == '?') s[L] = s[R];
            else s[R] = s[L];
        }
        else if (s[L] == '?') s[L] = s[R] = 'a';
        ++L, --R;
    }
    if (L == R && s[L] == '?') s[L] = 'a';
    cout << s;
    return 0;
}