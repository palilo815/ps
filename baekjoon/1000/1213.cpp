#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int cnt[26];
int main() {
    string s; cin >> s;
    for (char c : s) ++cnt[c - 'A'];

    int odd = 0;
    char odd_char = '\0';
    loop(i, 26) if (cnt[i] % 2) {
        ++odd;
        odd_char = i + 'A';
    }

    if (odd > 1) {
        cout << "I'm Sorry Hansoo";
        return 0;
    }

    stack<char> stk;
    loop(i, 26)  while (cnt[i] >= 2) {
        cout << (char)(i + 'A');
        stk.emplace(i + 'A');
        cnt[i] -= 2;
    }

    if (odd_char) cout << odd_char;

    while (!stk.empty()) {
        cout << stk.top(); stk.pop();
    }
    return 0;
}