#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool sieve[100001], visited[1000001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    sieve[0] = sieve[1] = true;
    for (int i = 2;i <= 100000;++i)
        if (!sieve[i])
            for (int j = i * 2;j <= 100000;j += i)
                sieve[j] = true;

    int T; cin >> T;
    while (T--) {
        int N, A, B; cin >> N >> A >> B;
        set<int> prime;
        for (int i = A;i <= B;++i)
            if (!sieve[i])
                prime.insert(i);
        if (prime.empty()) {
            cout << -1 << '\n';
            continue;
        }
        memset(visited, 0, sizeof(visited));
        visited[N] = true;
        int ans = 0;
        queue<int> q;
        q.push(N), q.push(-1);
        while (1) {
            int curr = q.front(); q.pop();
            if (curr == -1) {
                ++ans; q.push(curr);
                continue;
            }
            if (prime.find(curr) != prime.end()) break;
            if (curr + 1 < 1000001 && !visited[curr + 1]) {
                visited[curr + 1] = true;
                q.push(curr + 1);
            }
            if (curr - 1 >= 0 && !visited[curr - 1]) {
                visited[curr - 1] = true;
                q.push(curr - 1);
            }
            if (!visited[curr / 2]) {
                visited[curr / 2] = true;
                q.push(curr / 2);
            }
            if (!visited[curr / 3]) {
                visited[curr / 3] = true;
                q.push(curr / 3);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}