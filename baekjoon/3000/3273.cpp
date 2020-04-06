#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int arr[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> arr[i];
    sort(arr, arr + N);

    int sum; cin >> sum;
    int ans = 0;
    for (int i = 0; i < N && arr[i] <= sum / 2; ++i)
        if (binary_search(arr + i + 1, arr + N, sum - arr[i]))
            ++ans;
    cout << ans;
}