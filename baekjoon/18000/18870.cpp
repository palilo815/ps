#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000000;

int arr[max_N];
int srr[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> arr[i];
    
    memcpy(srr, arr, sizeof(int) * N);
    sort(srr, srr + N);

    int M = unique(srr, srr + N) - srr;
    loop(i, N) cout << lower_bound(srr, srr + M, arr[i]) - srr << ' ';
    return 0;
}