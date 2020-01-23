#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    set<int> A;
    set<int>::iterator it;
    int a, b, num;
    cin >> a >> b;
    // A의 원소를 다 집어넣음
    while (a--) {
        cin >> num;
        A.insert(num);
    }
    // 그 중 B에 속하는 것들 제거
    while (b--) {
        cin >> num;
        it = A.find(num);
        if (it != A.end())
            A.erase(it);
    }
    cout << A.size() << '\n';
    for (it = A.begin(); it != A.end();++it)
        cout << *it << ' ';
    return 0;
}