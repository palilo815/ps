#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int L, C;
char arr[15];
bool Mo[15];
vector<char> Ans;
void Code(int start, int num, int mo, int ja)
{
    if (Mo[start]) ++mo;
    else ++ja;
    if (num == 0) {
        if (mo > 0 && ja > 1) {
            for (char c : Ans) cout << c;
            cout << '\n';
        }
        return;
    }
    for (int next = start + 1; next + num - 1 < C; ++next) {
        Ans.push_back(arr[next]);
        Code(next, num - 1, mo, ja);
        Ans.pop_back();
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> L >> C;
    loop(i, C) cin >> arr[i];
    sort(arr, arr + C);
    loop(i, C)
        if (arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'i' || arr[i] == 'o' || arr[i] == 'u')
            Mo[i] = true;
    loop(i, C) {
        Ans.push_back(arr[i]);
        Code(i, L - 1, 0, 0);
        Ans.pop_back();
    }
    return 0;
}