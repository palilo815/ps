#include <bits/stdc++.h>
using namespace std;

bool appear[26];
int main()
{
    list<char> lst;
    int ans = 0, T = 52;
    char cow;
    while(T--) {
        cin >> cow;
        int c_num = cow - 'A';
        if (!appear[c_num]) {
            appear[c_num] = true;
            lst.push_back(cow);
        }
        else {
            // 소의 출발점과 도착점 사이의 다른 소의 개수를 더해준다.
            int cnt = lst.size() - 1;
            auto it = lst.begin();
            while (*it != cow) ++it, --cnt;
            ans += cnt;
            // 현재 소를 x, 나중에 나올 소를 y라 하면
            // y x x y 혹은 x x y y의 경우밖에 없다.
            // 절대 둘의 경로가 겹치지 않는다.
            lst.erase(it);
        }
    }
    cout << ans;
    return 0;
}