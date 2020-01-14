#include<iostream>
#include<algorithm>
using namespace std;

int money(int a, int b, int c)
{
    if (a == b) {
        if (a == c) return 10000 + a * 1000;
        else return 1000 + a * 100;
    }
    else {
        if (a == c) return 1000 + a * 100;
        else {
            if (b == c) return 1000 + b * 100;
            else {
                int x = max(a, b);
                x = max(x, c);
                return x * 100;
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int ans = 0, t, a, b, c;
    cin >> t;
    while (t--) {
        cin >> a >> b >> c;
        ans = max(ans, money(a, b, c));
    }
    cout << ans;
    return 0;
}