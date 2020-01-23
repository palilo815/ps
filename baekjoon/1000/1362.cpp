#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int o, w, T = 0;
    while (cin >> o >> w) {
        if (o == 0) break;
        char c; int n; bool alive = true;
        while (cin >> c >> n) {
            if (c == '#') break;
            if (alive) {
                if (c == 'F') w += n;
                else {
                    w -= n;
                    if (w <= 0) alive = false;
                }
            }
        }
        cout << ++T << ' ';
        if (!alive) cout << "RIP\n";
        else if (w > o / 2 && w < o * 2) cout << ":-)\n";
        else cout << ":-(\n";
    }
    return 0;
}