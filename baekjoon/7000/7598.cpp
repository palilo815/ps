#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int seat;
    while (1) {
        cin >> s >> seat;
        if (s == "#" && seat == 0) break;
        char op; int n;
        while (1) {
            cin >> op >> n;
            if (op == 'X') break;
            if (op == 'B' && seat + n <= 68) seat += n;
            else if (op == 'C' && seat - n >= 0) seat -= n;
        }
        cout << s << ' ' << seat << '\n';
    }
    return 0;
}