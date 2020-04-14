#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 100000;

int ans[max_N];
tup buy[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    set<p> fence;
    loop(i, N) {
        int h; cin >> h;
        fence.emplace(h, i);
    }

    loop(i, N) {
        int h, c; cin >> h >> c;
        buy[i] = { c,h,i + 1 };
    }
    sort(buy, buy + N, greater<tup>());

    int earn = 0;
    loop(i, N) {
        auto [c, h, idx] = buy[i];
        auto it = fence.upper_bound({ h + 1,-1 });
        if (it == fence.begin()) {
            it = fence.end();
            c = 0;
        }
        --it;

        earn += c;
        ans[it->second] = idx;
        fence.erase(it);
    }
    cout << earn << '\n';
    loop(i, N) cout << ans[i] << ' ';
    return 0;
}