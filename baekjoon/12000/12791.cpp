#include <bits/stdc++.h>
using namespace std;

typedef struct {
    int year;
    string name;
}album;

bool cmp(const album& a, const album& b) {
    return a.year < b.year;
}
int main()
{
    album arr[25];
    arr[0].year = 1967, arr[0].name = "DavidBowie";
    arr[1].year = 1969, arr[1].name = "SpaceOddity";
    arr[2].year = 1970, arr[2].name = "TheManWhoSoldTheWorld";
    arr[3].year = 1971, arr[3].name = "HunkyDory";
    arr[4].year = 1972, arr[4].name = "TheRiseAndFallOfZiggyStardustAndTheSpidersFromMars";
    arr[5].year = 1973, arr[5].name = "AladdinSane";
    arr[6].year = 1973, arr[6].name = "PinUps";
    arr[7].year = 1974, arr[7].name = "DiamondDogs";
    arr[8].year = 1975, arr[8].name = "YoungAmericans";
    arr[9].year = 1976, arr[9].name = "StationToStation";
    arr[10].year = 1977, arr[10].name = "Low";
    arr[11].year = 1977, arr[11].name = "Heroes";
    arr[12].year = 1979, arr[12].name = "Lodger";
    arr[13].year = 1980, arr[13].name = "ScaryMonstersAndSuperCreeps";
    arr[14].year = 1983, arr[14].name = "LetsDance";
    arr[15].year = 1984, arr[15].name = "Tonight";
    arr[16].year = 1987, arr[16].name = "NeverLetMeDown";
    arr[17].year = 1993, arr[17].name = "BlackTieWhiteNoise";
    arr[18].year = 1995, arr[18].name = "1.Outside";
    arr[19].year = 1997, arr[19].name = "Earthling";
    arr[20].year = 1999, arr[20].name = "Hours";
    arr[21].year = 2002, arr[21].name = "Heathen";
    arr[22].year = 2003, arr[22].name = "Reality";
    arr[23].year = 2013, arr[23].name = "TheNextDay";
    arr[24].year = 2016, arr[24].name = "BlackStar";

    int T; cin >> T;
    while (T--) {
        int y1, y2; cin >> y1 >> y2;
        album tmp;
        tmp.year = y1;
        auto it1 = lower_bound(arr, arr + 25, tmp, cmp);
        tmp.year = y2;
        auto it2 = upper_bound(arr, arr + 25, tmp, cmp);
        cout << it2 - it1 << '\n';
        while (it1 != it2) {
            cout << it1->year << ' ' << it1->name << '\n';
            ++it1;
        }
    }
    return 0;
}