#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

struct name {
    string F;
    string L;
};
bool cmp(name& A, name& B)
{
    if (A.L == B.L)
        return A.F < B.F;
    return A.L < B.L;
}
name s[100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> s[i].F >> s[i].L;
    sort(s, s + n, cmp);
    loop(i, n) cout << s[i].F << ' ' << s[i].L << '\n';
    return 0;
}