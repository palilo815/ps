#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n, start, end;
    cin >> n;

    vector<pair<int, int>> order;
    while (n-- > 0) {
        cin >> start >> end;
        order.push_back(make_pair(end, start));
    }
    sort(order.begin(), order.end());

    int earliest = 0, count = 0;
    for (int i = 0;i < order.size(); i++) {
        int meetingStart = order[i].second, meetingEnd = order[i].first;
        if (earliest <= meetingStart) {
            earliest = meetingEnd;
            count++;
        }
    }
    cout << count;
    return 0;
}