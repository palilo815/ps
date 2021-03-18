#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    int sum = 0;
    for (int x; n--;) {
        cin >> x;
        sum ^= x - 2;
    }

    string fst;
    cin >> fst;

    if (sum)
        cout << fst;
    else
        cout << (fst == "Blackking" ? "Whiteking" : "Blackking");
}