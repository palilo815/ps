#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int stock[100000];
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
int LIS(int size)
{
    vector<int> T(size);
    int length = 1;
    T[0] = stock[0];
    for (int i = 1; i < size; i++) {
        if (stock[i] < T[0])
            T[0] = stock[i];
        else if (stock[i] > T[length - 1])
            T[length++] = stock[i];
        else
            T[ceilElement(T, -1, length - 1, stock[i])] = stock[i];
    }
    return length;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    while (cin >> N) {
        loop(i, N) cin >> stock[i];
        cout << LIS(N) << '\n';
    }
    return 0;
}