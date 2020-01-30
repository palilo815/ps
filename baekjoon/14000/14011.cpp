#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000;

int arr[2][max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, money; cin >> N >> money;
    loop(i, 2) loop(j, N) cin >> arr[i][j];
    loop(i, N)
        if (arr[0][i] >= arr[1][i])
            arr[0][i] = INT_MAX;
    bool flag = true;
    while (flag) {
        flag = false;
        loop(i, N)
            if (arr[0][i] <= money) {
                money -= arr[0][i] - arr[1][i];
                arr[0][i] = INT_MAX;
                flag = true;
            }
    }
    cout << money;
    return 0;
}