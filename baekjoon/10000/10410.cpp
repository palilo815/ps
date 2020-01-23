#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, crs;
    cin >> n;
    string name, std, born;
    while (n--) {
        cin >> name >> std >> born >> crs;
        cout << name << ' ';
        int y = stoi(std.substr(0, 4));
        if (y >= 2010) { cout << "eligible\n"; continue; }
        y = stoi(born.substr(0, 4));
        if (y >= 1991) { cout << "eligible\n"; continue; }
        if (crs > 40) { cout << "ineligible\n"; continue; }
        cout << "coach petitions\n";
    }
    return 0;
}