#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int max_N = 100;

int N;
ll arr[max_N];
bool visited[max_N];
stack<ll> ans;

void DFS(int u) {
    if (visited[u]) return;
    visited[u] = true;
    ll val = arr[u];
    int v = lower_bound(arr, arr + N, 2 * val) - arr;

    // u의 다음이 될 수 있는 수는 2*u와 u/3이다.
    // arr에 둘 다 있을 수 없다.
    // u의 다음 수에서 어떤 연산을 하더라도 다시 u로 돌아오지 못하기 때문

    if (v != N && arr[v] == 2 * val) {
        DFS(v);
    }
    else if (val % 3 == 0) {
        v = lower_bound(arr, arr + N, val / 3) - arr;
        if (v != N && arr[v] == val / 3) DFS(v);
    }
    ans.push(u);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    loop(i, N) cin >> arr[i];
    sort(arr, arr + N);
    loop(i, N) DFS(i);
    while (!ans.empty()) {
        cout << arr[ans.top()] << ' ';
        ans.pop();
    }
    return 0;
}