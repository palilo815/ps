#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct lawnmower {
    string name;
    int p, c, t, r;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int64_t week = 10080;

    int l, n;
    cin >> l >> n;
    cin.ignore();

    vector<lawnmower> a(n);
    for (auto& [name, p, c, t, r] : a) {
        string s;
        getline(cin, s);

        size_t comma;
        name = s.substr(0, comma = s.find(','));
        s.erase(0, comma + 1);

        p = stoi(s.substr(0, comma = s.find(',')));
        s.erase(0, comma + 1);

        c = stoi(s.substr(0, comma = s.find(',')));
        s.erase(0, comma + 1);

        t = stoi(s.substr(0, comma = s.find(',')));
        s.erase(0, comma + 1);

        r = stoi(s);
    }

    int mn = INT_MAX;
    for (auto& [name, p, c, t, r] : a) {
        if (week * c * t / (t + r) >= l)
            chmin(mn, p);
        else
            p = -1;
    }

    if (mn == INT_MAX)
        cout << "no such mower";
    else
        for (auto& x : a)
            if (x.p == mn)
                cout << x.name << '\n';
}