#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int L1, L2, L3, cache[100][100][100];
string s1, s2, s3;

int LCS(int a, int b, int c)
{
    if (a == L1 || b == L2 || c == L3) return 0;
    int& ret = cache[a][b][c];
    if (ret != -1) return ret;

    if ((s1[a] == s2[b]) && (s2[b] == s3[c]))
        return ret = 1 + LCS(a + 1, b + 1, c + 1);

    ret = max(LCS(a + 1, b, c), LCS(a, b + 1, c));
    return ret = max(ret, LCS(a, b, c + 1));
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(cache, -1, sizeof(cache));
    cin >> s1 >> s2 >> s3;
    L1 = s1.length(), L2 = s2.length(), L3 = s3.length();
    cout << LCS(0, 0, 0);
    return 0;
}