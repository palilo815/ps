#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;

int get_num(char c, string& key)
{
    int len = key.size();
    loop(i, len) if (key[i] == c) return -(i + 1);
    return 0;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s, key;
    cin >> s >> key;

    // key가 1글자면 단순하게 처리 가능
    if (key.size() == 1) {
        char k = key[0]; bool FRULA = true;
        for (char x : s)
            if (x != k) {
                cout << x;
                FRULA = false;
            }
        if (FRULA) cout << "FRULA";
        return 0;
    }

    deque<P> dq;
    int len = s.size(), last = key.size();
    last = -last;

    // dq에 pair<int,int>를 집어넣는데,
    // 만약 폭발 문자열에 포함 안되는 문자일 경우
    // string에서의 index를 넣는다 ({i,i})

    // 만약 폭발 문자열에 포함이 될 경우
    // 폭발 문자열과 얼마나 일치하는지 그 범위 [a,b]를 넣는다


    // 여기선 stack처럼 쓰이고
    loop(i, len) {
        int idx = get_num(s[i], key);
        if (idx == 0) dq.push_back({ i,i });
        else {
            if (dq.empty() || dq.back().first >= 0)
                dq.push_back({ idx,idx });
            else {
                P p = dq.back();
                if (p.second - 1 == idx) {
                    dq.pop_back();
                    if (p.first != -1 || idx != last)
                        dq.push_back({ p.first,idx });
                }
                else dq.push_back({ idx,idx });
            }
        }
    }

    // 여기선 queue처럼 쓰인다.
    if(dq.empty()) cout << "FRULA";
    else
        while (!dq.empty()) {
            P p = dq.front();
            if (p.first >= 0) cout << s[p.first];
            else {
                for (int i = p.first; i >= p.second; --i)
                    cout << key[-i - 1];
            }
            dq.pop_front();
        }
    return 0;
}