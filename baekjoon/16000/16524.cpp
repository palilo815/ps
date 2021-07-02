#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    unordered_set<string> st;

    for (string s; n--;) {
        cin >> s;

        const auto provider = s.find('@');
        assert(provider != string::npos);

        auto it = s.find('+');
        if (it == string::npos)
            it = provider;

        s.erase(remove(s.begin(), s.begin() + it, '.'), s.begin() + provider);
        st.emplace(s);
    }
    cout << st.size();
}