#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int A[2] = { 1,4 }, B[3] = { 3,5,6 };
int like(string& s)
{
    if (s.size() != 7) return 0;
    char a = s[0], b = s[2];
    if (a == b) return 0;
    loop(i, 2) if (a != s[A[i]]) return 0;
    loop(i, 3) if (b != s[B[i]]) return 0;
    return 1;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        string s; cin >> s;
        cout << like(s) << '\n';
    }
    return 0;
}