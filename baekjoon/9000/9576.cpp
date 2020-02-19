#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_stdt = 1000;
const int max_book = 1000;

p want[max_stdt];
bool selected[max_book + 1];

bool cmp(const p& a, const p& b)
{
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int B, S; cin >> B >> S;
        loop(i, S) cin >> want[i].first >> want[i].second;
        sort(want, want + S, cmp);

        int ans = 0;
        memset(selected, 0, sizeof(selected));
        loop(i, S) for (int j = want[i].first; j <= want[i].second; ++j)
            if (!selected[j]) {
                selected[j] = true;
                ++ans;
                break;
            }
        cout << ans << '\n';
    }
    return 0;
}