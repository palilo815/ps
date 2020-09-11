#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int a, b, c, d; cin >> a >> b >> c >> d;

    vector<int> A(a), B(b), C(c), D(d);
    for (int& x : A) cin >> x;
    for (int& x : B) cin >> x;
    for (int& x : C) cin >> x;
    for (int& x : D) cin >> x;

    unordered_set<int> st;
    for (int& x : C)
        for (int& y : D)
            st.emplace(x + y);

    int k = 0;
    for (int& x : A)
        for (int& y : B)
            if (st.count(-(x + y))) {
                cout << x << ' ' << y;
                k = -(x + y);
                goto out;
            }
out:
    sort(D.begin(), D.end());
    for (int& x : C)
        if (binary_search(D.begin(), D.end(), k - x)) {
            cout << ' ' << x << ' ' <<  k - x;
            break;
        }
    return 0;
}