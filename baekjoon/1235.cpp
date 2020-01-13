#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string arr[1000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> arr[i];

    // 계산을 위한 k의 최솟값을 설정한다.
    // 만약 n = 100이면, 정말 운이 좋을 경우 딱 뒤의 2자리만으로 구별이 가능하다.
    int k = 1;
    while (pow(10, k) < n) ++k;

    int len = arr[0].size();
    bool fail = true;
    while (fail) {
        fail = false;
        set<string> st;
        loop(i, n) {
            string num = arr[i].substr(len - k, len);
            if (st.find(num) != st.end()) { fail = true; break; }
            st.insert(num);
        }
        if (fail) ++k;
    }
    cout << k;
    return 0;
}