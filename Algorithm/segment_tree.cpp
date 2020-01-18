#include <bits/stdc++.h> 
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[100];
int construct_segT(vector<int>& segT, int l, int r, int idx)
{
    if (l == r)
        return segT[idx] = arr[l];

    int mid = l + (r - l) / 2;
    return segT[idx] = min(construct_segT(segT, l, mid, idx * 2 + 1),
        construct_segT(segT, mid + 1, r, idx * 2 + 2));
}
int minQ(vector<int>& segT, int l, int r, int ql, int qr, int idx)
{
    // total overlap
    if (ql <= l && r <= qr)
        return segT[idx];
    // no overlap
    if (r < ql || qr < l)
        return INT_MAX;
    // partial overlap
    int mid = l + (r - l) / 2;
    return min(minQ(segT, l, mid, ql, qr, 2 * idx + 1),
        minQ(segT, mid + 1, r, ql, qr, 2 * idx + 2));
}
int main()
{
    int n; cin >> n;
    loop(i, n) cin >> arr[i];
    int log_2 = (int)(ceil(log2(n)));
    vector<int> segtree(2 * pow(2, log_2) - 1);
    construct_segT(segtree, 0, n - 1, 0);
    loop(i, n) for (int j = i;j < n;++j)
        printf("min of [%d,%d] : %d\n", i, j, minQ(segtree, 0, n - 1, i, j, 0));
    return 0;
}