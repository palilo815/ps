#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string lights = "N", tmp;
    cin >> tmp;
    lights += tmp;

    int len = lights.size(), ans = 0;
    loop(i, len)
        if (lights[i] == 'Y') {
            ++ans;
            for (int j = i * 2;j < len;j += i) {
                if (lights[j] == 'Y')
                    lights[j] = 'N';
                else
                    lights[j] = 'Y';
            }
        }
    cout << ans;
    return 0;
}