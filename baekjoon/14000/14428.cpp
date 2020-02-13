#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

int arr[max_N];
p segT[131072 * 2 - 1];

p build_segT(int l, int r, int idx)
{
    if (l == r) return segT[idx] = { arr[l],l };

    int mid = l + (r - l) / 2;
    return segT[idx] = min(build_segT(l, mid, 2 * idx + 1), build_segT(mid + 1, r, 2 * idx + 2));
}
p minQ(int ql, int qr, int l, int r, int idx)
{
    if (ql <= l && r <= qr) return segT[idx];
    if (r < ql || qr < l) return { INT_MAX,0 };
    int mid = l + (r - l) / 2;
    return min(minQ(ql, qr, l, mid, 2 * idx + 1), minQ(ql, qr, mid + 1, r, 2 * idx + 2));
}
void update(int ui, int uv, int l, int r, int idx)
{
    if (l == r) {
        arr[ui] = uv;
        segT[idx] = { uv,ui };
    }
    else {
        int mid = l + (r - l) / 2;
        if (ui <= mid) update(ui, uv, l, mid, 2 * idx + 1);
        else update(ui, uv, mid + 1, r, 2 * idx + 2);
        segT[idx] = min(segT[2 * idx + 1], segT[2 * idx + 2]);
    }

}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> arr[i];
    build_segT(0, N - 1, 0);
    
    int Q; cin >> Q;
    while (Q--) {
        int q, a, b; cin >> q >> a >> b;
        if (q == 1) update(a - 1, b, 0, N - 1, 0);
        else cout << minQ(a - 1, b - 1, 0, N - 1, 0).second + 1 << '\n';
    }
    return 0;
}