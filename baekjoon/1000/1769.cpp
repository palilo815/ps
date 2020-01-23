#include<iostream>
#include<string>
using namespace std;
int Sum(int n)
{
    int ret = 0;
    while (n) {
        ret += n % 10;
        n /= 10;
    }
    return ret;
}
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int x = 0, ans = 0;
    if (s.length() == 1) x = stoi(s);
    else {
        for (int i = 0; i < s.length(); ++i)
            x += s[i] - '0';
        ans++;
    }
    while (x > 9) {
        ans++;
        x = Sum(x);
    }
    cout << ans << '\n';
    if (x % 3 == 0) cout << "YES";
    else cout << "NO";
    return 0;
}