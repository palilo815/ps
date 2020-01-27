#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int len; string s;
    cin >> len >> s;
    long long ans = 0;
    loop(i, len)
        if (s[i] <= '9') {
            int num = 0;
            int j = i;
            while (j < len && s[j] <= '9') {
                num *= 10;
                num += s[j] - '0';
                ++j;
            }
            i = j - 1;
            ans += num;
        }
    cout << ans;
    return 0;
}