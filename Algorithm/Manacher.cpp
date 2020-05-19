#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000;

char s[max_N * 2 + 1];  // s = #s#t#r#i#n#g#
int p[max_N * 2 + 1];   // p[i] : i를 중심으로 하는 palindrome 반지름

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string str; cin >> str;
    int N = 1;
    for (char c : str) {
        s[N] = c;
        N += 2;
    }

    int l = 0, r = -1, k;
    for (int i = 0; i < N; ++i) {
        if (i > r) k = 0;
        else k = min(p[l + r - i], r - i);

        while (i - k - 1 >= 0 && i + k + 1 < N && s[i - k - 1] == s[i + k + 1])
            ++k;

        p[i] = k;
        if (i + k > r)
            l = i - k, r = i + k;
    }
    return 0;
}