#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string name[20];
char msg[20][20];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t = 0;
    while (++t) {
        int n; cin >> n;
        if (!n) break;

        loop(i, n) {
            cin >> name[i];
            loop(j, n - 1) cin >> msg[i][j];
        }

        cout << "Group " << t << '\n';
        bool blame = false;
        loop(i, n) loop(j, n)
            if (msg[i][j] == 'N') {
                int idx = i - j - 1;
                if (idx < 0) idx += n;
                cout << name[idx] << " was nasty about " << name[i] << '\n';
                blame = true;
            }
        if (!blame) cout << "Nobody was nasty\n";
        cout << '\n';
    }
    return 0;
}