#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define M 100000
bool cache[M];

int MSD(int n)
{
    int ret = 1;
    while (n > 9) {
        n /= 10;
        ret *= 10;
    }
    return ret;
}
int ButtonB(int num)
{
    num *= 2;
    num -= MSD(num);
    return num;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, T, G;
    cin >> N >> T >> G;

    queue<int> q;
    q.push(N), q.push(-1);
    cache[N] = true;
    int ans = 0;
    bool flag = true;

    while (1) {
        int n = q.front(); q.pop();
        if (n == -1) {
            ++ans;
            if (q.empty() || ans > T) {
                flag = false;
                break;
            }
            q.push(n);
            continue;
        }
        if (n == G) break;
        if (n + 1 < M && !cache[n + 1]) {
            cache[n + 1] = true;
            q.push(n + 1);
        }
        int B = ButtonB(n);
        if (n > 0 && n * 2 < M && !cache[B]) {
            cache[B] = true;
            q.push(B);
        }
    }
    if (flag) cout << ans;
    else cout << "ANG";
    return 0;
}