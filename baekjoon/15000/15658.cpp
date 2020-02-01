#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int n, arr[11], OP[4], ans_max, ans_min;
void BF(int sum, int ind)
{
    if (ind == n) {
        ans_max = max(ans_max, sum);
        ans_min = min(ans_min, sum);
        return;
    }
    if (OP[0] > 0) {
        --OP[0];
        BF(sum + arr[ind], ind + 1);
        ++OP[0];
    }
    if (OP[1] > 0) {
        --OP[1];
        BF(sum - arr[ind], ind + 1);
        ++OP[1];
    }
    if (OP[2] > 0) {
        --OP[2];
        BF(sum * arr[ind], ind + 1);
        ++OP[2];
    }
    if (OP[3] > 0) {
        --OP[3];
        BF(sum / arr[ind], ind + 1);
        ++OP[3];
    }
}
int main()
{
    cin >> n;
    loop(i, n) cin >> arr[i];
    loop(i, 4) cin >> OP[i];

    ans_max = INT_MIN, ans_min = INT_MAX;
    BF(arr[0], 1);
    cout << ans_max << '\n' << ans_min;
    return 0;
}