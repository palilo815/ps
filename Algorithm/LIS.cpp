#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000000;

int arr[max_N], T[max_N + 1];
int ceil_elem(int s, int e, int key) {
    while (e - s > 1) {
        int mid = s + (e - s) / 2;
        if (T[mid] >= key)
            e = mid;
        else
            s = mid;
    }
    return e;
}
int LIS(int N) {
    int len = 1;
    T[1] = arr[0];

    for (int i = 1; i < N; ++i) {
        if (arr[i] < T[1])
            T[1] = arr[i];
        else if (arr[i] > T[len])
            T[++len] = arr[i];
        else
            T[ceil_elem(0, len, arr[i])] = arr[i];
    }
    return len;
}