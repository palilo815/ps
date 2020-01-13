#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[100000];
int ceil_elem(vector<int>& T, int start, int end, int key) {
    while (end - start > 1) {
        int mid = start + (end - start) / 2;
        if (T[mid] >= key)
            end = mid;
        else
            start = mid;
    }
    return end;
}
int LIS(int size)
{
    vector<int> T(size);
    int length = 1;
    T[0] = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < T[0])
            T[0] = arr[i];
        else if (arr[i] > T[length - 1])
            T[length++] = arr[i];
        else
            T[ceil_elem(T, -1, length - 1, arr[i])] = arr[i];
    }
    return length;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // nlogn LIS algorithm
    int n; cin >> n;
    loop(i, n) cin >> arr[i];
    cout << n - LIS(n);
    return 0;
}