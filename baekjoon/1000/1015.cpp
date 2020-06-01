#include <bits/stdc++.h>
using namespace std;

const int max_N = 50;

pair<int, int> arr[max_N];
int ans[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> arr[i].first,
        arr[i].second = i;

    sort(arr, arr + N);
    for (int i = 0; i < N; ++i)
        ans[arr[i].second] = i;
    for (int i = 0; i < N; ++i)
        cout << ans[i] << ' ';
    return 0;
}