#include <bits/stdc++.h>
using namespace std;

int cnt_L[10];
int cnt_S[10];
string dst;
string L, S;

bool make_L(int pos, bool large) {
    if (pos == dst.size()) return true;
    int idx = large ? 0 : dst[pos] - '0';
    for (int i = idx; i < 10; ++i) if (cnt_L[i]) {
        --cnt_L[i], L += i + '0';
        if (make_L(pos + 1, large || (i > idx))) return true;
        ++cnt_L[i], L.pop_back();
    }
    return false;
}
bool make_S(int pos, bool small) {
    if (pos == dst.size()) return S != dst;
    int idx = small ? 9 : dst[pos] - '0';
    for (int i = idx; i >= 0; --i) if (cnt_S[i]) {
        --cnt_S[i], S += i + '0';
        if (make_S(pos + 1, small || (i < idx))) return true;
        ++cnt_S[i], S.pop_back();
    }
    return false;
}
int main() {
    string src;
    cin >> dst >> src;
    for (char c : src)
        ++cnt_L[c - '0'], ++cnt_S[c - '0'];

    if (!make_L(0, 0)) L = "0";
    if (!make_S(0, 0) || S[0] == '0') S = "0";
    cout << L << '\n' << S;
    return 0;
}