#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000000;

int arr[max_N];
int T[max_N + 1];
int R[max_N];

int ceil_elem(int l, int r, int key) {
    while (l + 1 < r) {
        int m = (l + r) >> 1;
        arr[T[m]] < key ? (l = m) : (r = m);
    }
    return r;
}
void print_ans(int idx) {
    if (idx == -1) return;
    print_ans(R[idx]);
    cout << arr[idx] << ' ';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> arr[i];

    memset(R, -1, sizeof(R));
    T[0] = -1;
    int len = 1;

    for (int i = 1; i < N; ++i) {
        if (arr[i] < arr[T[1]])
            T[1] = i;
        else if (arr[i] > arr[T[len]]) {
            R[i] = T[len];
            T[++len] = i;
        }
        else {
            int idx = ceil_elem(0, len, arr[i]);
            R[i] = T[idx - 1];
            T[idx] = i;
        }
    }

    cout << len << '\n';
    print_ans(T[len]);
    return 0;
}