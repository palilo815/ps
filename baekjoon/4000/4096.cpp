#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool Pallin(string& s)
{
    int L = 0, R = s.size() - 1;
    while (L < R)
        if (s[L++] != s[R--]) return false;
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (cin >> s) {
        if (s == "0") break;
        // 이미 팰린드롬이면 0
        if (Pallin(s)) cout << '0' << '\n';
        // 1334번 소스를 이용, 팰린드롬 수를 찾은 뒤
        // 현재 숫자를 뺴준다.
        else {
            string tmp = s;
            bool bigger = false;
            int L = 0, R = s.length() - 1;
            while (R - L > 0) {
                if (s[L] > s[R]) bigger = true;
                else if (s[L] < s[R]) bigger = false;
                s[R--] = s[L++];
            }
            if (!bigger) {
                if (L == R) {
                    s[L]++;
                    while (s[L] > '9') {
                        s[L--] = '0', s[R++] = '0';
                        s[L]++, s[R]++;
                    }
                }
                else {
                    s[--L]++, s[++R]++;
                    while (s[L] > '9') {
                        s[L--] = '0', s[R++] = '0';
                        s[L]++, s[R]++;
                    }
                }
            }
            long long ans = (long long)stol(s) - (long long)stol(tmp);
            cout << ans << '\n';
        }
    }
    return 0;
}