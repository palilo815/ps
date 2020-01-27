#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 10000;

int ROW[max_N + 1], COL[max_N + 1];
int B_srch(int arr[], int e)
{
    int s = 1, sum = INT_MAX, ret;
    while (s <= e) {
        int m = s + (e - s) / 2;
        int left = 0, right = 0;
        for (int i = 1;i < m;++i)
            left += arr[i];
        for (int i = max_N;i > m;--i)
            right += arr[i];
        ret = m;

        // m을 기준으로 왼쪽과 오른쪽에 있는 점의 개수의 균형이 맞으면 break
        if (left > right + arr[m]) e = m - 1;
        else if (left + arr[m] < right) s = m + 1;
        else break;
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int s = 1, e, dots;
    cin >> e >> dots;
    while (dots--) {
        int y, x; cin >> y >> x;
        ++ROW[y], ++COL[x];
    }

    int y = B_srch(ROW, e);
    int x = B_srch(COL, e);
    int ans = 0;
    for (int i = 1;i <= e;++i) {
        ans += ROW[i] * abs(y - i);
        ans += COL[i] * abs(x - i);
    }
    cout << ans;
    return 0;
}