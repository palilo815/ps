#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
using namespace std;
const int max_N = 100000;

int course[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    ll dist;
    cin >> N >> dist;
    loop(i, N) cin >> course[i];

    int idx = 0;
    while (idx < N && dist >= course[idx])
        dist -= course[idx++];
    if (idx == N) {
        --idx;
        while (dist >= course[idx])
            dist -= course[idx--];
    }
    cout << idx + 1;
    return 0;
}