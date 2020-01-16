#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int req[10000];
bool BS(int money, int N, int budget)
{
    int cost = 0;
    loop(i, N) {
        if (req[i] > money) cost += money;
        else cost += req[i];
    }
    if (cost > budget) return false;
    else return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, budget;
    cin >> N;
    loop(i, N) cin >> req[i];
    cin >> budget;

    int ans = 0;
    int s = 0, e = 0;
    // 이 문제는 budget의 최대 크기가, req[i]의 최대 크기를 넘으므로
    // e제한을 따로 설정해줘야 함.
    loop(i, N) e = max(e, req[i]);

    while (s <= e) {
        int mid = s + (e - s) / 2;
        if (BS(mid, N, budget)) {
            s = mid + 1;
            ans = mid;
        }
        else
            e = mid - 1;
    }
    cout << ans;
    return 0;
}