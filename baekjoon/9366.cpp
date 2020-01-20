#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int t, Tri[3];
    scanf("%d", &t);
    for (int i = 1;i <= t; ++i) {
        loop(i, 3) scanf("%d", &Tri[i]);
        sort(Tri, Tri + 3);
        printf("Case #%d: ", i);
        if (Tri[0] + Tri[1] <= Tri[2]) printf("invalid!\n");
        else {
            if (Tri[0] == Tri[1]) {
                if (Tri[1] == Tri[2]) printf("equilateral\n");
                else printf("isosceles\n");
            }
            else {
                if (Tri[1] == Tri[2]) printf("isosceles\n");
                else printf("scalene\n");
            }
        }
    }
    return 0;
}