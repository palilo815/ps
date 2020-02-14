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
void query(vector<vector<int>*>& vt, int ql, int qr, int l, int r, int idx)
{
    if (ql <= l && r <= qr) {
        vt.push_back(&segT[idx]);
        return;
    }
    if (qr < l || r < ql) return;
    int m = l + (r - l) / 2;
    query(vt, ql, qr, l, m, 2 * idx + 1);
    query(vt, ql, qr, m + 1, r, 2 * idx + 2);
    return;
}
int kth_num(int ql, int qr, int k, int N)
{
    // [ql,qr] 범위의 segT의 포인터를 vt에 담는다.
    vector<vector<int>*> vt;
    query(vt, ql, qr, 0, N - 1, 0);

    // 이분탐색으로 k번째 요소를 찾는다.
    // cnt : m보다 작은 숫자의 개수
    int s = -1000000000, e = 1000000000;
    int ret = 0;
    while (s <= e) {
        int m = s + (e - s) / 2;
        int cnt = 0;
        for (auto ptr : vt)
            cnt += lower_bound(ptr->begin(), ptr->end(), m) - ptr->begin();
        if (cnt > k - 1)
            e = m - 1;
        else {
            ret = m;
            s = m + 1;
        }
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    for (int i = 0; i < N; ++i)
        cin >> arr[i];

    build_segT(0, N - 1, 0);

    while (Q--) {
        int a, b, k; cin >> a >> b >> k;
        cout << kth_num(a - 1, b - 1, k, N) << '\n';
    }
    return 0;
}