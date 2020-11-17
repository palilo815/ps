#include "bogoSort.h"
#include <bits/stdc++.h>
using namespace std;

void sort_array(int N) {
    vector<int> a = copy_array();

    int s = -1;
    for (int i = 0; i < a.size(); ++i)
        if (i != a[i]) {
            s = i;
            break;
        }
    if (s == -1) return;

    int e = find(a.begin() + s + 1, a.end(), s) - a.begin();
    shuffle_array(s, e);
    sort_array(N);
}