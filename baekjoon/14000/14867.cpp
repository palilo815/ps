#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

set<P> cache;
queue<P> q;

void solve(int a, int b) {
    P p = make_pair(a, b);
    if (cache.find(p) != cache.end()) return;
    cache.insert(p);
    q.push(p);
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    q.push(make_pair(0, 0));
    q.push(make_pair(-1, -1));
    int A, B, X, Y;	//(A,B) -> (X,Y)    
    cin >> A >> B >> X >> Y;

    int ans = 0;
    while (1) {
        int a = q.front().first, b = q.front().second; q.pop();
        if (a == -1) {
            if (q.empty()) {
                ans = -1;
                break;
            }
            ++ans;
            q.push(make_pair(a, b));
            continue;
        }
        if (a == X && b == Y) break;
        solve(a, 0), solve(0, b), solve(A, b), solve(a, B);
        int mov = min(a, B - b);
        solve(a - mov, b + mov);
        mov = min(b, A - a);
        solve(a + mov, b - mov);
    }
    cout << ans;
    return 0;
}