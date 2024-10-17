#include <bits/stdc++.h>
using namespace std;

auto ask(int i) -> int {
    cout << "Q " << i << endl;
    int res;
    cin >> res;
    return res;
}

auto gotcha(int i) -> char {
    cout << "A " << i << endl;
    char res;
    cin >> res;
    return res;
}

auto main() -> int {
    int n, t;
    cin >> n >> t;
    vector<int> ids(n), check(n + 1);
    iota(ids.begin(), ids.end(), 1);
    random_device dev;
    mt19937 rng(dev());
    while (t--) {
        shuffle(ids.begin(), ids.end(), rng);
        fill(check.begin(), check.end(), 0);
        for (auto const& i : ids) {
            if (!check[i]) {
                auto const j = ask(i);
                if (i == j) {
                    if (gotcha(i)) {
                        break;
                    } else {
                        return 0;
                    }
                }
                check[i] = check[j] = 1;
            }
        }
    }
}
