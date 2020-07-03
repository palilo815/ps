#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using p = pair<int, int>;

const int M = 1000;

p poly[M];
int arr[M], ans[M];

int ccw(int i, int j, int k) {
    p& a = poly[i], & b = poly[j], & c = poly[k];
    int ret = (b.x - a.x) * (c.y - a.y) -
              (b.y - a.y) * (c.x - a.x);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
int dist(int i) {
    p& u = poly[arr[0]], & v = poly[i];
    int dx = u.x - v.x, dy = u.y - v.y;
    return dx * dx + dy * dy;
}
vector<int> convex_hull(int N) {
    swap(arr[0], *min_element(arr, arr + N, [&](int& i, int& j) -> bool {
        return poly[i] < poly[j];
    }));
    sort(arr + 1, arr + N, [&](int& i, int& j) -> bool {
        int ret = ccw(arr[0], i, j);
        return ret ? ret == 1 : dist(i) < dist(j);
    });

    vector<int> hull;
    loop(i, N) {
        while (hull.size() > 1 && ccw(hull[hull.size() - 2], hull[hull.size() - 1], arr[i]) <= 0)
            hull.pop_back();
        hull.emplace_back(arr[i]);
    }
    return hull;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> poly[i].x >> poly[i].y;
    iota(arr, arr + N, 0);

    int cnt = N;
    for (int t = 1; cnt >= 3; ++t) {
        auto hull = convex_hull(cnt);
        if (hull.size() < 3) break;
        cnt -= hull.size();

        int i = 0, j = 0;
        for (int& x : hull) {
            ans[x] = t;
            while (arr[j] ^ x)
                arr[i++] = arr[j++];
            ++j;
        }
    }
    loop(i, N) cout << ans[i] << ' ';
    return 0;
}