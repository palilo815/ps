#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

auto cmp = [](const p& a, const p& b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
};
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ifstream if1, if2;
    if1.open("tratincice/tratincice.in.4");
    if2.open("tratincice/tratincice.out.4");

    int ans1, ans2;
    if2 >> ans1 >> ans2;
    cout << ans1 << ' ' << ans2 << endl;

#define cin if1

    set<p> st1;
    set<p, decltype(cmp)> st2(cmp);

    int N, Q; cin >> N >> Q;
    while (N--) {
        int x, y; cin >> x >> y;
        st1.emplace(x, y);
        st2.emplace(x, y);
    }

    int x = 0, y = 0, X, Y;
    string query; cin >> query;

    for(char q : query){
        if (q == 'U' || q == 'D') {
            auto it = st1.find(make_pair(x, y));
            q == 'D' ? --it : ++it;
            X = it->first, Y = it->second;
        }
        else {
            auto it = st2.find(make_pair(x, y));
            q == 'L' ? --it : ++it;
            X = it->first, Y = it->second;
        }

        /*st1.erase(make_pair(x, y));
        st2.erase(make_pair(x, y));*/
        x = X, y = Y;
    }
    cout << x << ' ' << y;
    return 0;
}