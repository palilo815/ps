#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

int CeilingTo2(int n)
{
    --n;
    int pos = 0;
    while (n) {
        n = n >> 1;
        ++pos;
    }
    return 1 << pos;
}

struct RMQ {
    int n;
    vector<int> rangeMin, rangeMax;
    RMQ(const vector<int>& arr) {
        n = arr.size();
        int ST_size = 2 * CeilingTo2(n);
        rangeMin.resize(ST_size);
        rangeMax.resize(ST_size);
        init(arr, 0, n - 1, 1);
    }
    P init(const vector<int>& arr, int left, int right, int node) {
        if (left == right)
            return make_pair(rangeMin[node] = arr[left], rangeMax[node] = arr[left]);
        int mid = (left + right) / 2;
        P L = init(arr, left, mid, 2 * node);
        int leftMin = L.first, leftMax = L.second;
        P R = init(arr, mid + 1, right, 2 * node + 1);
        int rightMin = R.first, rightMax = R.second;
        return make_pair(rangeMin[node] = min(leftMin, rightMin), rangeMax[node] = max(leftMax, rightMax));
    }
    P query(int left, int right, int node, int nodeleft, int noderight) {
        if (right < nodeleft || noderight < left) return make_pair(INT32_MAX, INT32_MIN);
        if (left <= nodeleft && noderight <= right) return make_pair(rangeMin[node], rangeMax[node]);
        int mid = (nodeleft + noderight) / 2;
        P L = query(left, right, node * 2, nodeleft, mid);
        P R = query(left, right, node * 2 + 1, mid + 1, noderight);
        return make_pair(min(L.first, R.first), max(L.second, R.second));
    }
    P query(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
};
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m; cin >> n >> m;
    vector<int> vt(n);
    vt.reserve(n);
    loop(i, n) cin >> vt[i];

    RMQ Query(vt);
    int l, r;
    while (m--) {
        cin >> l >> r;
       P ans = Query.query(l - 1, r - 1);
        cout << ans.first << ' ' << ans.second << '\n';
    }
    return 0;
}