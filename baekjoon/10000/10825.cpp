#include <bits/stdc++.h>
using namespace std;
struct s {
    string name;
    int kor, eng, math;
} a[100000];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].name >> a[i].kor >> a[i].eng >> a[i].math;
    sort(a, a + N, [](auto & a, auto & b) -> bool {
        return a.kor == b.kor ? a.eng == b.eng ? a.math == b.math ? a.name < b.name : a.math > b.math : a.eng < b.eng : a.kor > b.kor;
    });
    for (int i = 0; i < N; ++i)
        cout << a[i].name << '\n';
    return 0;
}