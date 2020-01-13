#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    bool T[50];
    while (cin >> n) {
        if (!n) break;
        memset(T, 0, sizeof(T));
        while (n--) {
            loop(i, 6) {
                int x; cin >> x;
                T[x] = true;
            }
        }
        for (int i = 1; i < 50; ++i) {
            if (!T[i]) {
                cout << "No\n";
                break;
            }
            if (i == 49)
                cout << "Yes\n";
        }
    }
    return 0;
}