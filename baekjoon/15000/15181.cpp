#include <bits/stdc++.h>
using namespace std;

bool good(string& s)
{
    int len = s.size();
    for (int i = 1; i < len; ++i) {
        int gap = s[i] - s[i - 1];
        if (gap <= 0) gap = abs(gap) + 1;
        if (gap % 2) return false;
    }
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string music;
    while (1) {
        cin >> music;
        if (music == "#") break;
        if (good(music)) cout << "That music is beautiful.\n";
        else cout << "Ouch! That hurts my ears.\n";
    }
    return 0;
}