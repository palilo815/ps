#include<iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n1, n2;
        n1 = (s[0] - 'A') * 26 * 26 + (s[1] - 'A') * 26 + s[2] - 'A';
        n2 = (s[4] - '0') * 1000 + (s[5] - '0') * 100 + (s[6] - '0') * 10 + s[7] - '0';
        if (n1 - n2 > 100 || n1 - n2 < -100) cout << "not nice\n";
        else cout << "nice\n";
    }
    return 0;
}