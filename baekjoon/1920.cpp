#include<iostream>
#include<algorithm>
#include<set>
#include<iterator>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    set<int> st;
    int n, m, num;

    cin >> n;
    while (n-- > 0) {
        cin >> num;
        st.insert(num);
    }
    cin >> m;
    while (m-- > 0) {
        cin >> num;
        if (st.find(num) == st.end())
            cout << "0\n";
        else
            cout << "1\n";
    }
    return 0;
}