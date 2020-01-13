#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool Leak[1001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, L;
    cin >> n >> L;
    while (n--) {
        int x; cin >> x;
        Leak[x] = true;
    }

    int ans = 0;
    loop(i, 1001)
        if (Leak[i]) {
            ++ans;
            loop(j, L) {
                if (i + j > 1000) break;
                Leak[i + j] = false;
            }
        }
    cout << ans;
    return 0;
}