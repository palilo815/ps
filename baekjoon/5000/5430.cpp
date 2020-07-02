#include <bits/stdc++.h>
using namespace std;

const int M = 100000;

int dq[M];
int d, i, j;
char c;

bool error() {
    string s; cin >> s;
    cin >> j >> c;
    for (i = 0; i < j; ++i)
        cin >> dq[i] >> c;
    if (!j) cin >> c;

    i = 0, d = 1;
    for (char& c : s) {
        if (c == 'R') {
            swap(i, j);
            j += (d = -d);
        }
        else if (i == j) return true;
        i += d;
    }

    for (cout << '['; i ^ j; i += d) {
        cout << dq[i];
        if ((i + d) ^ j) cout << ',';
    }
    cout << "]\n";
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--)
        if (error())
            cout << "error\n";
    return 0;
}