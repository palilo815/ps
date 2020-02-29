#include <bits/stdc++.h>
using namespace std;
int i;
char ucpc[4] = { 'U','C','P','C' };
int main() {
    string s; getline(cin, s);
    for (char c : s) if (c == ucpc[i]) if (++i == 4) break;
    cout << "I " << (i == 4 ? "love" : "hate") << " UCPC";
    return 0;
}