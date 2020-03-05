#include<bits/stdc++.h>
using namespace std;

const int max_N = 1000000;

int arr[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        for (int i = 0; i < N; ++i) cin >> arr[i];
        sort(arr, arr + N);
        int M; cin >> M;
        while (M--) {
            int x; cin >> x;
            cout << binary_search(arr, arr + N, x) << '\n';
        }
    }
    return 0;
}