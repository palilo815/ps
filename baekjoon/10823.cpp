#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s, f = "";
    while (cin >> s) f += s;
    int num = 0;
    long long ans = 0;
    for(char c : f) {
        if (c == ',') {
            ans += num;
            num = 0;
        }
        else
            num = num * 10 + c - '0';
    }
    cout << ans + num;
    return 0;
}