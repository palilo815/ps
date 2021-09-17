#include <bits/stdc++.h>
using namespace std;

int kth(std::vector<int>& a, int k) {
    --k;
    nth_element(a.begin(), a.begin() + k, a.end());
    return a[k];
}