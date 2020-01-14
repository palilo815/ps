#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s[3];
    int Ans[3] = {};

    loop(i, 3) cin >> s[i];
    loop(i, 3) {
        int tmp = 1;
        for (int j = 1; j < 8; ++j) {
            if (s[i][j] == s[i][j - 1]) ++tmp;
            else {
                Ans[i] = max(Ans[i], tmp);
                tmp = 1;
            }
        }
        Ans[i] = max(Ans[i], tmp);
    }
    loop(i, 3) cout << Ans[i] << '\n';
    return 0;
}