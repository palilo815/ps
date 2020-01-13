#include<iostream>
#include<list>
#include<iterator>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;
    list<int> LIST;
    bool flag = true;
    for (int i = 1;i < n + 1;i++)
        LIST.push_back(i);
    list<int>::iterator kill = LIST.begin();

    while (n-- > 0) {
        for (int i = 0; i < k - 1; i++) {
            kill++;
            if (kill == LIST.end()) kill = LIST.begin();
        }
        if (flag) {
            cout << '<' << *kill;
            flag = false;
        }
        else cout << ", " << *kill;
        kill = LIST.erase(kill);
        if (kill == LIST.end()) kill = LIST.begin();
    }
    cout << '>';
    return 0;
}