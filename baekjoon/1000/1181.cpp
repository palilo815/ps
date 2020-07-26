#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 2e4;

string s[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> s[i];

    sort(s, s + N, [&](auto & a, auto & b) -> bool {
        return a.size() == b.size() ? a < b : a.size() < b.size();
    });
    N = unique(s, s + N) - s;
    loop(i, N) cout << s[i] << '\n';
    return 0;
}