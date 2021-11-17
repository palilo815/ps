#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    sort(a.begin(), a.end(), greater());
    int rmost = 0;
    for (int i = 0; i < n; ++i) {
        chmax(rmost, i + a[i]);
        if (rmost <= i) a[i] = -1;
    }
    fill_n(a.begin(), rmost - n, 0);
    cout << n - count(a.begin(), a.end(), -1);
}
