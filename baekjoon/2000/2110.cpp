#include<iostream>
#include<algorithm>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int n, c, house[200000];
bool BS(int dist)
{
    int cnt = 1, loc = house[0];
    for (int i = 1; i < n; ++i) {
        if (house[i] - loc >= dist) {
            ++cnt;
            loc = house[i];
        }
    }
    if (cnt < c) return false;
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n >> c;
    loop(i, n) cin >> house[i];
    sort(house, house + n);
    int s = 1, e = 1000000000, m, ans;
    while (s <= e) {
        m = s + (e - s) / 2;
        if (BS(m)) {
            ans = m;
            s = m + 1;
        }
        else
            e = m - 1;
    }
    cout << ans;
    return 0;
}