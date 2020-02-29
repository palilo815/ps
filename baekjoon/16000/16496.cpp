#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000;

string arr[max_N];

bool cmp(const string & a, const string & b) {
    int A = a.size(), B = b.size();
    for (int i = 0, j = 0; i < A || j < B; ++i, ++j)
        if (a[i % A] != b[j % B]) return a[i % A] > b[j % B];
    return false;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> arr[i];
    sort(arr, arr + N, cmp);
    // ... 이딴 tc는 왜 있는걸까
    if (arr[0] == "0") { cout << 0; return 0; }
    loop(i, N) cout << arr[i];
    return 0;
}