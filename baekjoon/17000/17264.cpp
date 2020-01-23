#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, P, w, l, goal, score = 0;
    cin >> N >> P >> w >> l >> goal;
    set<string> win_P;
    string s;
    while (P--) {
        char c;
        cin >> s >> c;
        if (c == 'W') win_P.insert(s);
    }

    // 입력받은 s가 win_P에 있으면 이기고
    // 없으면 무조건 진다.
    while (N--) {
        cin >> s;
        if (win_P.find(s) != win_P.end()) {
            score += w;
            if (score >= goal) break;
        }
        // 점수는 0점 미만이 될 수 없다
        else score = max(0, score - l);
    }
    cout << "I AM ";
    if (score >= goal) cout << "NOT ";
    cout << "IRONMAN!!";
    return 0;
}