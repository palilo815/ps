#include <bits/stdc++.h>
using namespace std;

int p1[26], p2[26];

void input(stack<int>& stk) {
    string s;
    while (1) {
        cin >> s;
        if (s == "end") return;
        stk.emplace(s == "nil" ? -1 : s[0] - 'A');
    }
}
void build_tree(stack<int>& stk, int parent, int p[]) {
    int u = stk.top(); stk.pop();
    if (u == -1) return;

    p[u] = parent;
    build_tree(stk, u, p);
    build_tree(stk, u, p);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    stack<int> stk1, stk2;
    int T; cin >> T;
start:;
    memset(p1, 0, sizeof(p1));
    memset(p2, 0, sizeof(p2));

    input(stk1);
    input(stk2);

    build_tree(stk1, -1, p1);
    build_tree(stk2, -1, p2);

    int flag = 1;
    for (int i = 0; i < 26; ++i)
        if (p1[i] != p2[i]) {
            flag = 0;
            break;
        }
    cout << (flag ? "true" : "false") << '\n';

    if (--T) goto start;
    return 0;
}