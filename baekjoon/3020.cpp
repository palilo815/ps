#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int bot[100000], top[100000];
int crash(int N, int H, int height)
{
    int ret = 0;
    int s = 0, e = N - 1, tmp = N;
    while (s <= e) {
        int m = s + (e - s) / 2;
        if (bot[m] < height) s = m + 1;
        else {
            e = m - 1;
            tmp = m;
        }
    }
    ret += N - tmp;
    height = H - height + 1;
    s = 0, e = N - 1, tmp = N;
    while (s <= e) {
        int m = s + (e - s) / 2;
        if (top[m] < height) s = m + 1;
        else {
            e = m - 1;
            tmp = m;
        }
    }
    ret += N - tmp;
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, H; cin >> N >> H;
    N /= 2;
    loop(i, N)  cin >> bot[i] >> top[i];
    sort(bot, bot + N);
    sort(top, top + N);

    int ans = 2 * N, cnt = 0;
    for (int i = 1; i <= H; ++i) {
        int tmp = crash(N, H, i);
        if (tmp == ans) ++cnt;
        else if (tmp < ans) ans = tmp, cnt = 1;
    }
    cout << ans << '\n' << cnt;
    return 0;
}