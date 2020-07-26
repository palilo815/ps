#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 8;
const int mxL = 20;

string w[mxN];
int M, K, ord[mxN], lps[mxN * mxL];
char s[(mxN * mxL) << 1];

int solve() {
    int cnt = 0;
    for (int i = 1, j = 0; i < M; ++i) {
        while (j && s[i] ^ s[j]) j = lps[j - 1];
        if (s[i] == s[j]) lps[i] = ++j;
    }
    for (int i = 0, j = 0; i < (M << 1) - 1; ++i) {
        while (j && s[i] ^ s[j]) j = lps[j - 1];
        if (s[i] == s[j] && ++j == M)
            ++cnt, j = lps[j - 1];
    }
    return cnt == K;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> w[i];
    loop(i, N) M += w[i].size();
    iota(ord, ord + N, 0);

    cin >> K;
    int ans = 0;
    do {
        char* ptr = s;
        loop(i, N) ptr = copy(w[ord[i]].begin(), w[ord[i]].end(), ptr);
        copy(s, ptr, ptr);
        ans += solve();
    } while (next_permutation(ord, ord + N));
    cout << ans;
    return 0;
}