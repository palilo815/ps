#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int max_N = 5000;

int arr[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> arr[i];
    sort(arr, arr + N);

    ll _min = INT64_MAX;
    int a, b, c;
    for (int i = 0; i < N - 2; ++i) for (int j = i + 1; j < N - 1; ++j) {
        int key = arr[i] + arr[j];
        auto it = lower_bound(arr + j + 1, arr + N, -key);
        ll tmp;

        if (it != arr + N) {
            tmp = abs((ll)key + *it);
            if (tmp < _min) {
                a = i, b = j, c = it - arr;
                _min = tmp;
            }
        }

        --it;
        if (it != arr + j) {
            tmp = abs((ll)key + *it);
            if (tmp < _min) {
                a = i, b = j, c = it - arr;
                _min = tmp;
            }
        }
    }
    cout << arr[a] << ' ' << arr[b] << ' ' << arr[c];
    return 0;
}