#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 소수의 곱들을 priority_queue에 넣는다.
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> prime;
    int k, n; cin >> k >> n;
    loop(i, k) {
        int x; cin >> x;
        prime.push_back(x);
        pq.push(x);
    }
    ll num;
    // pq에서 n번째 뽑히는 숫자가 정답이다.
    loop(i, n) {
        num = pq.top(); pq.pop();
        loop(j, k) {
            ll value = num * (ll)prime[j];
            // 정답은 INT32_MAX이하라고 했으므로,
            // 넘는 수는 제외해도 된다.
            if (value > INT32_MAX) break;
            pq.push(value);

            // 소수를 중복해서 세면 안된다.
            // 앞에서 a*b*c를 구해서 abc를 pq에 넣었으면
            // 뒤에서 a*c*b를 또 넣어선 안된다.
            // num이 prime[j]로 나누어 떨어진단 뜻은,
            // num을 pq에 넣었을 때, num과 j이후의 소수들의 곱을 이미 구해서
            // pq에 같이 넣었단 뜻이므로, 중단해야 한다.
            if (num % prime[j] == 0)
                break;
        }
    }
    cout << num;
    return 0;
}