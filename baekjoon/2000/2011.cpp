#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define MOD 1000000

int Code[5000], LEN, Cache[5000];
int DP(int start)
{
    if (start == LEN) return 1;
    int& ret = Cache[start];
    if (ret != -1) return ret;

    ret = 0;
    int Num = Code[start];
    if (Num) {
        ret += DP(start + 1);
        if (start + 1 < LEN) {
            int BigNum = Num * 10 + Code[start + 1];
            if (BigNum <= 26)
                ret += DP(start + 2);
        }
    }
    ret %= MOD;
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(Cache, -1, sizeof(Cache));
    string s; cin >> s;
    LEN = s.length();
    loop(i, LEN) Code[i] = s[i] - '0';
    cout << DP(0);
    return 0;
}