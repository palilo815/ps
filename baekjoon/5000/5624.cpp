#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 5000;
const int x = 200000;

int arr[max_N];
bool sum[x * 2 + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    int ans = 0;
    loop(i, N) {
        cin >> arr[i];
        loop(j, i) if (sum[arr[i] - arr[j] + x]) {
            ++ans;
            break;
        }
        sum[arr[i] * 2 + x] = true;
        loop(j, i) sum[arr[i] + arr[j] + x] = true;
    }
    cout << ans;
    return 0;
}