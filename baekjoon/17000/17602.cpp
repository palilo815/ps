#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

// flag : 다른 문자가 나온 적이 있는지 여부
int palin(string& s, int L, int R, bool flag)
{
    if (L < R) {
        // 두 문자가 똑같다면 계속 진행
        if (s[L] == s[R])
            return palin(s, L + 1, R - 1, flag);
        // 두 문자가 다르고, 이전에 달랐던 적이 있으면 2
        if (flag) return 2;
        // 두 문자가 다르고, 이전에 달랐던 적이 없으면, flag = true로 바꾸고 진행
        if (palin(s, L + 1, R, true) == 0 || palin(s, L, R - 1, true) == 0) return 1;
        else return 2;
    }
    return 0;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        string n; cin >> n;
        cout << palin(n, 0, n.size() - 1, false) << '\n';
    }
    return 0;
}