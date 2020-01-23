#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

// 해당 숫자가 사전순으론 몇 번째인지.
// ex) 0은 zero라서 사전상 가장 뒤이므로 9
int dic[10] = { 9,4,8,7,2,1,6,5,0,3 };

bool MySort(int a, int b)
{
    int Fa, Fb;
    // 먼저 앞 글자로 비교한다.
    if (a > 9) Fa = a / 10;
    else Fa = a % 10;
    if (b > 9) Fb = b / 10;
    else Fb = b % 10;
    if (Fa != Fb) return dic[Fa] < dic[Fb];

    // 앞 글자가 똑같으면 뒷 글자로 비교한다.
    a -= Fa * 10, b -= Fb * 10;
    // 만약 둘 중 하나가 한 글자라면, 그게 앞으로 간다.
    if (a < 0) return true;
    if (b < 0) return false;
    return dic[a] < dic[b];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b; cin >> a >> b;
    vector<int> vt;
    for (int i = a; i <= b; ++i)
        vt.push_back(i);
    sort(vt.begin(), vt.end(), MySort);
    loop(i, vt.size()) {
        cout << vt[i] << ' ';
        if ((i + 1) % 10 == 0) cout << '\n';
    }
    return 0;
}