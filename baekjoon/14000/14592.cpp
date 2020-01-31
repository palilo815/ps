#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 3;

typedef struct {
    int score;
    int submit;
    int last;
} info;
info arr[max_N];
bool my_comp(int win, int i)
{
    if (arr[win].score == arr[i].score) {
        if (arr[win].submit == arr[i].submit)
            return arr[win].last > arr[i].last;
        return arr[win].submit > arr[i].submit;
    }
    return arr[win].score < arr[i].score;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> arr[i].score >> arr[i].submit >> arr[i].last;

    int win = 0;
    for (int i = 1; i < n; ++i)
        if (my_comp(win, i))
            win = i;
    cout << win + 1;
    return 0;
}