#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool Pallin(string& s)
{
    int L = 0, R = s.size() - 1;
    while (L < R) {
        char l = s[L], r = s[R];
        if (l >= 'A' && l <= 'Z') l += 32;
        if (r >= 'A' && r <= 'Z') r += 32;
        if (l != r) return false;
        ++L, --R;
    }
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    cin.ignore();
    while (T--) {
        string s; getline(cin, s);
        if (Pallin(s)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}