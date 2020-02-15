#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int price[10];
int selected[10];
int minQ(int s, int e)
{
    int ret = INT_MAX;
    for (int i = s; i <= e; ++i)
        ret = min(ret, price[i]);
    return ret;
}
int main()
{
    int N; cin >> N;
    loop(i, N) cin >> price[i];
    int money; cin >> money;

    if (N == 1) { cout << 0; return 0; }

    int min_cost = minQ(1, N - 1);
    if (money < min_cost) { cout << 0; return 0; }

    int len = 1 + ((money - min_cost) / min(min_cost, price[0]));
    for (int i = N - 1; i > 0; --i) {
        if (price[i] * len <= money) {
            selected[i] = len;
            len = 0;
            break;
        }
        int tmp = minQ(0, i - 1), cnt = 0;
        while (len && (money - price[i] >= tmp * (len - 1))) {
            money -= price[i];
            ++cnt, --len;
        }
        selected[i] = cnt;
    }
    bool flag = true;
    for (int i = N - 1; i > 0; --i) while (selected[i]--) {
        cout << i;
        flag = false;
    }
    if (flag) len = 1;
    while (len--) cout << 0;
    return 0;
}