#include<iostream>
using namespace std;

int main()
{
    int t, a, b, c;
    char o, x;
    string s[2] = { "NO","YES" };
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> a >> o >> b >> x >> c;
        cout << "Case " << i << ": ";
        if (o == '+') cout << s[a + b == c];
        else cout << s[a - b == c];
        cout << '\n';
    }
    return 0;
}