#include <bits/stdc++.h>
using namespace std;

char DP[51][51][51][3][3];

char top_down(int a, int b, int c, int p1, int p2) {
    if (a + b + c == 0) return 1;
    char& ret = DP[a][b][c][p1][p2];
    if (ret != -1) return ret;

    ret = 0;
    if (a && top_down(a - 1, b, c, p2, 0))
        return ret = 'A';
    if (b && p2 != 1 && top_down(a, b - 1, c, p2, 1))
        return ret = 'B';
    if (c && p1 != 2 && p2 != 2 && top_down(a, b, c - 1, p2, 2))
        return ret = 'C';
    return ret;
}
void print_ans(int a, int b, int c, int p1, int p2) {
    if (a + b + c == 0) return;
    char x = DP[a][b][c][p1][p2];
    cout << x;
    if (x == 'A') print_ans(a - 1, b, c, p2, 0);
    else if (x == 'B') print_ans(a, b - 1, c, p2, 1);
    else print_ans(a, b, c - 1, p2, 2);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(DP, -1, sizeof(DP));
    int a = 0, b = 0, c = 0;

    string s; cin >> s;
    for (char x : s) {
        if (x == 'A') ++a;
        else if (x == 'B') ++b;
        else ++c;
    }
    
    if (!top_down(a, b, c, 0, 0)) {
        cout << -1;
        return 0;
    }
    print_ans(a, b, c, 0, 0);
    return 0;
}