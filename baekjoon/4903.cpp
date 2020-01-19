#include<bits/stdc++.h>
using namespace std;
int fact(int n)
{
    int ret = 1;
    while (n > 0) {
        ret *= n;
        --n;
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b;
    while (cin >> a >> b) {
        if (a == -1) break;
        cout << a << '+' << b;
        int tmp = fact(a + b) / fact(a) / fact(b);
        if (tmp == a + b) cout << '=';
        else cout << "!=";
        cout << a + b << '\n';
    }
    return 0;
}