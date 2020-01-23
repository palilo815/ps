#include<iostream>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int lesson[100000];
bool Make(int size, int N, int max_cnt)
{
    int tmp = 0, count = 1;
    loop(i, N) {
        if (lesson[i] > size) return false;
        if (tmp + lesson[i] > size)
            tmp = 0, ++count;
        tmp += lesson[i];
    }
    if (count > max_cnt) return false;
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, cnt;
    cin >> N >> cnt;;
    loop(i, N) cin >> lesson[i];

    int s = 1, e = 1000000000, ans;
    while (s <= e) {
        int mid = s + (e - s) / 2;
        if (Make(mid, N,cnt)) {
            ans = mid;
            e = mid - 1;
        }
        else s = mid + 1;
    }
    cout << ans;
    return 0;
}