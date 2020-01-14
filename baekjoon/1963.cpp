#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool sieve[10001], visited[10001];
int make0(int num, int digit)
{
    int tmp = num % digit;
    digit *= 10;
    num = num / digit * digit;
    return num + tmp;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    sieve[0] = sieve[1] = true;
    for (int i = 2; i < 10000; ++i)
        if (!sieve[i])
            for (int j = 2 * i;j < 10000;j += i)
                sieve[j] = true;

    int T; cin >> T;
    while (T--) {
        queue<int> q;
        int a, b; cin >> a >> b;
        q.push(a), q.push(-1);
        visited[a] = true;
        int ans = 0;
        while (1) {
            int x = q.front(); q.pop();
            // pivot
            if (x == -1) {
                if (q.empty()) break;
                ++ans; q.push(x);
                continue;
            }
            // find answer
            if (x == b) break;
            // move
            loop(i, 4) {
                // 10^i의 자릿수를 0으로 만들어서 tmp에 저장
                int digit = pow(10, i);
                int tmp = make0(x, digit);
                loop(j, 10) {
                    // 앞 자리가 0인 경우
                    if (i == 3 && j == 0) continue;
                    int N = tmp + j * digit;
                    if (!sieve[N] && !visited[N]) {
                        visited[N] = true;
                        q.push(N);
                    }
                }
            }
        }
        if (q.empty()) cout << "Impossible\n";
        else cout << ans << '\n';
        memset(visited, 0, sizeof(visited));
    }
    return 0;
}