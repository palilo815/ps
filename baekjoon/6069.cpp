#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool bulb[501];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    while (M--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op) {
            int ans = 0;
            for (int i = a; i <= b; ++i)
                if (bulb[i]) ++ans;
            cout << ans << '\n';
        }
        else {
            for (int i = a; i <= b; ++i)
                bulb[i] = !bulb[i];
        }
    }
    return 0;
}