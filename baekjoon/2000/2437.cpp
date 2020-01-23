#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int weight[1000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> weight[i];
    sort(weight, weight + n);
    if (weight[0] > 1) { cout << 1; return 0; }
    // 1g 추가 없는 경우 답은 무조건 1

    // psum : [0,i)번 추들의 무게 합
    int psum = 0, ans = 0;
    loop(i, n) {
        int w = weight[i];
        if (psum + 1 < w) {
            ans = psum + 1;
            break;
        }
        psum += weight[i];
    }

    if (ans) cout << ans;
    else cout << psum + 1;
    return 0;
}