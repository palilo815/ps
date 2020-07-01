#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
    int ret = (x1 * y2 + x2 * y3 + x3 * y1) -
              (y1 * x2 + y2 * x3 + y3 * x1);
    if (ret > 0) return 1;
    else if (ret < 0) return -1;
    return 0;
}

bool cross(p& a, p& b, p& c, p& d) {
    int abc = ccw(a, b, c);
    int abd = ccw(a, b, d);
    int cda = ccw(c, d, a);
    int cdb = ccw(c, d, b);

    if (abc * abd == 0 && cda * cdb == 0)
    {
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);

        return a <= d && c <= b;
    }

    return abc * abd <= 0 && cda * cdb <= 0;
}