#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[2][3];
bool Same()
{
    loop(i, 3)
        if (arr[0][i] != arr[1][i]) return false;
    return true;
}
int M_of_3()
{
    int sum = 0;
    loop(i, 3) sum += arr[0][i] / 10 + arr[0][i] % 10;
    if (sum % 3) return 0;
    return 1;
}
void add_T()
{
    ++arr[0][2];
    if (arr[0][2] >= 60) {
        arr[0][2] = 0, ++arr[0][1];
        if (arr[0][1] >= 60) {
            arr[0][1] = 0, ++arr[0][0];
            if (arr[0][0] == 24) arr[0][0] = 0;
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s[2];
    while (cin >> s[0] >> s[1]) {
        int ans = 0;
        loop(i, 2) loop(pos, 3)
            arr[i][pos] = (s[i][pos * 3] - '0') * 10 + s[i][pos * 3 + 1] - '0';
        while (1) {
            ans += M_of_3();
            if (Same()) break;
            add_T();
        }
        cout << ans << '\n';
    }
    return 0;
}