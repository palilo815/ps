#include <bits/stdc++.h>
using namespace std;

const int M = 5e3;

char s[M + 1];
int lps[M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> s;
    int ans = 0;
    for (int k = 0; s[k]; lps[++k] = 0) {
        int i = k + 1;
        for (int j = 0; s[i]; ++i) {
            while (j && s[i] ^ s[k + j]) j = lps[k + j - 1];
            lps[i] = s[i] == s[k + j] ? ++j : 0;
        }
        ans = max(ans, *max_element(lps + k, lps + i));
    }
    cout << ans;
    return 0;
}