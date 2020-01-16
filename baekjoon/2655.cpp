#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define LOOP(i,n) for(int i=1;i<=n;++i)
struct dol {
    int W;
    int A;
    int L;
    int num;
};
bool cmp(dol& a, dol& b) {
    return a.W > b.W;
}
dol arr[102];
int DP[102], LOG[102];
int main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    arr[0] = { INT32_MAX,INT32_MAX,0,0 };
    LOOP(i, N) {
        cin >> arr[i].A >> arr[i].L >> arr[i].W;
        arr[i].num = i;
    }
    arr[N + 1] = { 0,0,0,N + 1 };
    sort(arr, arr + N + 2, cmp);
    // arr : 무게 순으로 정렬됨

    //DP[N] : N번 블록을 꼭 사용해서 얻을 수 있는 가장 높은 탑
    LOOP(i, N + 1) {
        int id = 0;	// id :아래에 둘 수 있는 돌 중 가장 높이가 큰 애

        // j번 돌은 i번 돌보다 무조건 무겁다.
        // 따라서 i번 돌보다 면적이 큰 애들 중 가장 높은 DP값을 가진 애를 뽑는다.
        loop(j, i)
            if (arr[j].A > arr[i].A && DP[j] > DP[id])
                id = j;
        DP[i] = DP[id] + arr[i].L;
        LOG[i] = id;
    }

    // LOG[i] : i번 돌의 밑에 놓인 돌의 번호
    int ans = 0, curr = LOG[N + 1];
    vector<int> vt;
    while (arr[curr].num) {
        ++ans;
        vt.push_back(arr[curr].num);
        curr = LOG[curr];
    }
    cout << ans << '\n';
    for (int x : vt) cout << x << '\n';
    return 0;
}