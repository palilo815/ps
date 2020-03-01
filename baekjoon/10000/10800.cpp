#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 200000;
const int max_C = 200000;
const int max_S = 2000;

vector<p> ball[max_S + 1];
int psum[max_C + 1];
int ans[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) {
        int c, s; cin >> c >> s;
        ball[s].push_back({ c,i });
    }

    int S = 0;
    loop(s, max_S + 1) {
        for (auto [c, i] : ball[s])
            ans[i] = S - psum[c];
        for (auto [c, i] : ball[s])
            psum[c] += s;
        S += s * ball[s].size();
    }
    loop(i, N) cout << ans[i] << '\n';
    return 0;
}