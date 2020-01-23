#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    char c;
    int n; cin >> n; cin.ignore();
    while (n--) {
        list<char> PW;
        auto cursor = PW.end();
        while (cin.peek() != '\n') {
            cin >> c;
            if (c == '<') {
                if (cursor != PW.begin())
                    --cursor;
            }
            else if (c == '>') {
                if (cursor != PW.end())
                    ++cursor;
            }
            else if (c == '-') {
                if (cursor != PW.begin()) {
                    --cursor;
                    cursor = PW.erase(cursor);
                }
            }
            else
                PW.insert(cursor, c);
        }
        for (char x : PW) cout << x;
        cout << '\n';
        cin.ignore();
    }
    return 0;
}