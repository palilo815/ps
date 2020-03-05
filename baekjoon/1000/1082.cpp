#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int price[10];

int main()
{
    int N; cin >> N;
    loop(i, N) cin >> price[i];
    int money; cin >> money;
    if (N == 1) { cout << 0; return 0; }

    int a = N - 1;
    for (int i = N - 2; i > 0; --i) if (price[i] < price[a])
        a = i;
    if (money < price[a]) { cout << 0; return 0; }
    int b = (price[0] < price[a] ? 0 : a);

    vector<int> ans;
    ans.emplace_back(a);
    money -= price[a];
    while (1) {
        if (money - price[b] < 0) break;
        ans.emplace_back(b);
        money -= price[b];
    }

    for (int i = 0; money && i < ans.size(); ++i) {
        int cur = ans[i];
        for (int nxt = N - 1; nxt > cur; --nxt)
            if (money >= price[nxt] - price[cur]) {
                money -= price[nxt] - price[cur];
                ans[i] = nxt;
                break;
            }
    }
    for (int x : ans) cout << x;
    return 0;
}