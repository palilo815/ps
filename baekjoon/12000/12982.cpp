#include <bits/stdc++.h>
#define loop(i,n) for(int i=0; i<n; ++i)
using namespace std;

const int max_N = 100000;

int arr[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    int ans = 0;
    int N; cin >> N;
    loop(i, N) {
        int x; cin >> x;
        ans += x / N;
        arr[i] = x % N;
    }
    sort(arr, arr + N);

    int tmp = INT_MAX;
    loop(i, N) tmp = min(tmp, arr[i] + N - 1 - i);
    cout << ans + tmp;
    return 0;
}