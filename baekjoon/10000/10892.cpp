#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef struct {
    int x, y, idx;
} stick;

const int max_N = 300;

stick arr[3 * max_N];

bool cmp(const stick& a, const stick& b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    N *= 3;
    loop(i, N) {
        cin >> arr[i].x >> arr[i].y;
        arr[i].idx = i + 1;
    }
    sort(arr, arr + N, cmp);
    for (int i = 0; i < N; i += 3) {
        cout << arr[i].idx << ' ' << arr[i + 1].idx << ' ' << arr[i + 2].idx;
        cout << '\n';
    }
    return 0;
}