#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;

struct splitmix64_hash {
    // http://xorshift.di.unimi.it/splitmix64.c
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr array<pair<int, int>, 8> mov =
        {{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}};

    int n;
    string s;
    cin >> n >> s;

    hash_map<int64_t, int> vertexs;
    hash_set<int64_t> edges;

    int64_t x = n, y = n, nx, ny;
    int vtx_cnt = 0;

    vertexs[x << 32 | y] = vtx_cnt++;
    for (const auto& c : s) {
        nx = x + mov[c - '0'].first, ny = y + mov[c - '0'].second;
        if (vertexs.find(nx << 32 | ny) == vertexs.end())
            vertexs[nx << 32 | ny] = vtx_cnt++;
        edges.insert(int64_t(min(vertexs[x << 32 | y], vertexs[nx << 32 | ny])) << 32 |
                     max(vertexs[x << 32 | y], vertexs[nx << 32 | ny]));
        x = nx, y = ny;

        nx = x + mov[c - '0'].first, ny = y + mov[c - '0'].second;
        if (vertexs.find(nx << 32 | ny) == vertexs.end())
            vertexs[nx << 32 | ny] = vtx_cnt++;
        edges.insert(int64_t(min(vertexs[x << 32 | y], vertexs[nx << 32 | ny])) << 32 |
                     max(vertexs[x << 32 | y], vertexs[nx << 32 | ny]));
        x = nx, y = ny;
    }
    cout << 1 + edges.size() - vertexs.size();
}