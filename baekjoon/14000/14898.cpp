#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000000;

int N;
int arr[max_N];
int nxt[max_N];

vector<int> segT[max_N * 2];

void init() {
    unordered_map<int, int> mp(N * 4);
    for (int i = N - 1; i >= 0; --i) {
        nxt[i] = mp[arr[i]] ? mp[arr[i]] - 1: INT_MAX;
        mp[arr[i]] = i + 1;
    }

    for (int i = 0; i < N; ++i)
        segT[i + N].emplace_back(nxt[i]);

    for (int i = N - 1; i; --i) {
        vector<int>& L = segT[i * 2], & R = segT[i * 2 | 1];
        segT[i].resize(L.size() + R.size());
        merge(L.begin(), L.end(), R.begin(), R.end(), segT[i].begin());
    }
}
int query(int l, int r) {
    int ret = 0, k = r;
    for (l += N, r += N; l < r; l /= 2, r /= 2) {
        if (l & 1) {
            ret += segT[l].end() - lower_bound(segT[l].begin(), segT[l].end(), k);
            ++l;
        }
        if (r & 1) {
            --r;
            ret += segT[r].end() - lower_bound(segT[r].begin(), segT[r].end(), k);
        }
    }
    return ret;
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> arr[i];

    init();

    int Q; cin >> Q;
    int ans = 0;
    while (Q--) {
        int x, r; cin >> x >> r;
        int l = x + ans;

        ans = query(l - 1, r);
        cout << ans << '\n';
    }
    return 0;
}