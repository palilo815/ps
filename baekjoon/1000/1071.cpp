#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    vector<int> vt(N);
    loop(i, N) cin >> vt[i];
    sort(vt.begin(), vt.end());

    /*
        vt를 정렬했을때
        1)  vt.front + 1 != vt.end인 경우
            vt.front를 제일 앞에 세워도 해를 찾을 수 있다.
            front를 제외한 나머지를 거꾸로 뒤집으면 절대 연속된 요소가 나올 수 없기 때문
        2)  front == end인 경우
            front를 앞에 놓을 경우 해를 찾을 수 없다.
            a a a a (a+1) (a+1) (a+1)꼴이란 얘긴데, a를 맨 앞에 두면 a뒤에 (a+1)이 반드시 등장한다.
            이 경우 가능한 해는, 뒷부분을 전부 뒤집는 것 뿐이다.
        따라서 (2)인 경우가 등장하면 뒷부분을 전부 뒤집고, 아니라면 넣을 수 있는 최솟값을 넣으면서 진행한다.
    */

    vector<int> ans;
    while (!vt.empty()) {
        if (vt.front() + 1 == vt.back())
            while (!vt.empty()) {
                ans.push_back(vt.back());
                vt.pop_back();
            }
        for(auto it = vt.begin(); it!=vt.end(); ++it)
            if (ans.empty() || ans.back() + 1 != *it) {
                ans.push_back(*it);
                vt.erase(it);
                break;
            }
    }
    for (int x : ans) cout << x << ' ';
    return 0;
}