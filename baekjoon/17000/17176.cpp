#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int cnt[53];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;

    int x;
    while (N--) {
        cin >> x;
        ++cnt[x];
    }
    cin.ignore();

    string s; getline(cin, s);
    for (char c : s) {
        if (c == ' ') --cnt[0];
        else if (c < 'a') --cnt[c - 'A' + 1];
        else --cnt[c - 'a' + 27];
    }

    bool possible = true;
    loop(i, 53)
        if (cnt[i]) {
            possible = false;
            break;
        }
    if (possible) cout << 'y';
    else cout << 'n';
    return 0;
}