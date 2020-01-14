#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

// 열등한지 return
// 자기보다 a,b가 모두 작은 사원이 있는지 보면 된다.
bool poor(map<int, int>& mp, int a, int b)
{
    // 자신이 a등수가 몇 번째인지 구한다.
    auto it = mp.lower_bound(a);
    // 자기의 a등수가 가장 작다면 false
    if (it == mp.begin()) return false;
    // 자기의 a등수 바로 앞 사원의 b등수가 나보다 낮다면 true
    return b > (--it)->second;
}

// 자기보다 열등한 모든 사원 제거
void DeleteP(map<int, int>& mp, int a, int b)
{
    // it : 나의 a등수 위치
    auto it = mp.upper_bound(a);
    // ++it하면서 (나보다 a등수가 높은 애들을 중에)
    // 나보다 b등수가 높은 애들을 전부 지워버린다.
    while (it != mp.end()) {
        if (it->second < b) break;
        auto tmp = it;
        ++tmp;
        mp.erase(it);
        it = tmp;
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        map<int, int> mp;
        int n; cin >> n;
        while (n--) {
            int a, b; cin >> a >> b;
            if (poor(mp, a, b)) continue;
            mp[a] = b;
            DeleteP(mp, a, b);
        }
        cout << mp.size() << '\n';
    }
    return 0;
}