#include <iostream>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

string solve() {
    int N, r, c, x;
    cin >> N >> r >> c;
    --r, --c;
    int cmp = 0, me = 50001;
    loop(i, N) loop(j, N) {
        cin >> x;
        if (i == r || j == c) {
            if (i == r && j == c) me = x;
            else cmp = max(cmp, x);
            if (cmp > me) return "ANGRY";
        }
    }
    return "HAPPY";
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cout << solve();
    return 0;
}