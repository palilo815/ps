#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        string n1, n2; cin >> n1 >> n2;
        reverse(n1.begin(), n1.end());
        reverse(n2.begin(), n2.end());
        int a = stoi(n1), b = stoi(n2);
        a += b;
        n1 = to_string(a);
        reverse(n1.begin(), n1.end());
        a = stoi(n1);
        cout << a << '\n';
    }
    return 0;
}