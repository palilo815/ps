#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    ll a, b, c;
    while (T--) {
        cin >> a >> b >> c;
        ll S = max(a, b);
        S = max(S, c);
        ll B = a + b + c - S;
        cout << S * S + B * B << '\n';
    }
    return 0;
}