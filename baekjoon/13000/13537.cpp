#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int arr[max_N];
vector<int> segT[131072 * 2 - 1];

vector<int> merge_segT(vector<int>& a, vector<int>& b)
{
    int len_a = a.size(), len_b = b.size();
    vector<int> ret;
    ret.reserve(len_a + len_b);
    int i = 0, j = 0;
    while (i < len_a && j < len_b) {
        if (a[i] < b[j]) ret.push_back(a[i++]);
        else ret.push_back(b[j++]);
    }
    while (i < len_a) ret.push_back(a[i++]);
    while (j < len_b) ret.push_back(b[j++]);
    return ret;
}
void build_segT(int l, int r, int idx)
{
    if (l == r) {
        segT[idx].push_back(arr[l]);
        return;
    }
    int m = l + (r - l) / 2;
    build_segT(l, m, 2 * idx + 1);
    build_segT(m + 1, r, 2 * idx + 2);
    segT[idx] = merge_segT(segT[2 * idx + 1], segT[2 * idx + 2]);
}
int query(int ql, int qr, int k, int l, int r, int idx)
{
    if (ql <= l && r <= qr)
        return segT[idx].end() - upper_bound(segT[idx].begin(), segT[idx].end(), k);
    if (qr < l || r < ql)
        return 0;
    int m = l + (r - l) / 2;
    return query(ql, qr, k, l, m, 2 * idx + 1) + query(ql, qr, k, m + 1, r, 2 * idx + 2);
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
        int a, b, k; cin >> a >> b >> k;
        cout << query(a - 1, b - 1, k, 0, N - 1, 0) << '\n';
    }
    return 0;
}