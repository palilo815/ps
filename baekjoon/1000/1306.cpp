#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000000;

int light[max_N];
vector<int> seg_tree;

int build_tree(int l, int r, int idx)
{
    if (l == r) return seg_tree[idx] = light[l];
    int mid = l + (r - l) / 2;
    return seg_tree[idx] = max(build_tree(l, mid, 2 * idx + 1), build_tree(mid + 1, r, 2 * idx + 2));
}
int query(int ql, int qr, int l, int r, int idx)
{
    if (ql <= l && r <= qr) return seg_tree[idx];
    if (ql > r || qr < l) return INT_MIN;

    int mid = l + (r - l) / 2;
    return max(query(ql, qr, l, mid, 2 * idx + 1), query(ql, qr, mid + 1, r, 2 * idx + 2));
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    //** Range Maximum Query Seg-Tree **//

    int N, M; cin >> N >> M;
    loop(i, N) cin >> light[i];

    int log_2 = ceil(log2(N));
    seg_tree.resize(2 * pow(2, log_2) - 1);
    build_tree(0, N - 1, 0);

    loop(l, N - 2 * M + 2) {
        int r = l + 2 * M - 2;
        cout << query(l, r, 0, N - 1, 0) << ' ';
    }
    return 0;
}