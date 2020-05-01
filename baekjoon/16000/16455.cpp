#include<bits/stdc++.h>
using namespace std;

int pivot(vector<int>& arr, int l, int r) {
    int x = arr[r], i = l;
    for (int j = l; j <= r - 1; ++j) {
        if (arr[j] <= x) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}
int kth_smallest(vector<int>& arr, int l, int r, int k) {
    int idx = pivot(arr, l, r);
    if (idx - l == k - 1)
        return arr[idx];
    if (idx - l > k - 1)
        return kth_smallest(arr, l, idx - 1, k);
    return kth_smallest(arr, idx + 1, r, k - idx + l - 1);
}
int kth(vector<int>& a, int k) {
    return kth_smallest(a, 0, a.size() - 1, k);
}