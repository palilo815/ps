#include <bits/stdc++.h>
using namespace std;
typedef struct {
    int idx, T, S;
} work;

const int max_N = 1000;

work arr[max_N];

bool cmp(const work& a, const work& b) {
    int A = a.T * b.S, B = b.T * a.S;
    if (A == B) return a.idx < b.idx;
    return A < B;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        arr[i].idx = i + 1;
        cin >> arr[i].T >> arr[i].S;
    }
    sort(arr, arr + N, cmp);
    for (int i = 0; i < N; ++i) cout << arr[i].idx << ' ';
    return 0;
}