#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool check[26][26];
bool OMG(string& s)
{
    int len = s.size();
    for (int gap = 1; gap < len - 1; ++gap) {
        memset(check, 0, sizeof(check));
        loop(i, len - gap) {
            int prev = s[i] - 'A', curr = s[i + gap] - 'A';
            if (check[prev][curr]) return false;
            check[prev][curr] = true;
        }
    }
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (cin >> s) {
        if (s == "*") break;
        cout << s << " is ";
        if (!OMG(s)) cout << "NOT ";
        cout << "surprising.\n";
    }
    return 0;
}