#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int lego[1000000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int width;
    while (cin >> width) {
        width *= 10000000;
        int n; cin >> n;
        loop(i, n) cin >> lego[i];
        sort(lego, lego + n);

        int ans = -1;
        loop(i, n) {
            int key = lego[i];
            if (key > width / 2) break;
            if (binary_search(lego + i + 1, lego + n, width - key)) {
                ans = key;
                break;
            }
        }
        if (ans != -1) cout << "yes " << ans << ' ' << width - ans << '\n';
        else cout << "danger\n";
    }
    return 0;
}