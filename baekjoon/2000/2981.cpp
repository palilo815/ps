#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;
const int max_N = 100;

int arr[max_N];
int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}
void find_ans(vector<P>& vt, vector<int>& ans, int idx, int val)
{
    if (idx == vt.size()) {
        ans.push_back(val);
        return;
    }
    int num = vt[idx].first, cnt = vt[idx].second;
    loop(i, cnt + 1) {
        find_ans(vt, ans, idx + 1, val);
        val *= num;
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> arr[i];
    
    // x1, x2, x3 ... xn을 m으로 나눴을 때 나머지가 전부 n이라면,
    // x1 = y1m + n
    // x2 = y2m + n .. 이다.
    // 따라서 m은 xb - xa의 약수이다.

    // 모든 x쌍의 차이의 최대공약수를 g에 저장한다.
    sort(arr, arr + N);
    int g = arr[N - 1] - arr[0];
    loop(i, N - 1) for (int j = i + 1;j < N;++j)
        g = gcd(g, arr[j] - arr[i]);
    
    // g의 소인수분해 결과를 vt에 저장
    // ex) 56 = 2^3 * 7^1이므로
    // vt = {{2,3}, {7,1}}
    vector<P> vt;
    int i = 2;
    while (g > 1) {
        int cnt = 0;
        while (g % i == 0) {
            ++cnt;
            g /= i;
        }
        if(cnt) vt.push_back({ i,cnt });
        ++i;
    }

    // 소인수들의 모든 곱을 ans에 집어넣고, 정렬한 뒤 출력
    // ans[0] = 1이므로 0을 건너뛰고 1부터 출력한다.
    vector<int> ans;
    find_ans(vt, ans, 0, 1);
    sort(ans.begin(), ans.end());
    int len = ans.size();
    for (int i = 1;i < len;++i)
        cout << ans[i] << ' ';
    return 0;
}