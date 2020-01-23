#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int ceilElement(vector<int>& a, int start, int end, int key) {
    while (end - start > 1) {
        int mid = start + (end - start) / 2;
        if (a[mid] >= key)
            end = mid;
        else
            start = mid;
    }
    return end;
}
int LIS(vector<int>& input, int size)
{
    vector<int> T(size);
    int length = 1;
    T[0] = input[0];
    for (int i = 1; i < size; i++) {
        if (input[i] < T[0])
            T[0] = input[i];
        else if (input[i] > T[length - 1])
            T[length++] = input[i];
        else
            T[ceilElement(T, -1, length - 1, input[i])] = input[i];
    }
    return length;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    vector<int> vt(n);
    loop(i, n) cin >> vt[i];
    cout << LIS(vt, n);
    return 0;
}