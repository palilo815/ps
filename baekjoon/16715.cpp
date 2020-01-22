#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int N_zin(int num, int n)
{
    int ret = 0;
    while (num) {
        ret += num % n;
        num /= n;
    }
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int num; cin >> num;
    int max_num = 0, ans;
    for (int i = 2; i <= num; ++i) {
        int tmp = N_zin(num, i);
        if (tmp > max_num)
            max_num = tmp, ans = i;
    }
    cout << max_num << ' ' << ans;
    return 0;
}