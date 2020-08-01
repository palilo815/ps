#include <bits/stdc++.h>
using namespace std;

const string k[8] = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};

int main() {
    string s; cin >> s;
    for (int i = 0; i < 8; ++i)
        for (auto j = s.find(k[i]); ~j; j = s.find(k[i]))
            s.replace(j, k[i].size(), "_");
    cout << s.size();
    return 0;
}