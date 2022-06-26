#include <bits/stdc++.h>

constexpr std::array<std::array<char, 13>, 4> qwerty {{
    {'`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '='},
    {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\\'},
    {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\''},
    {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'},

}};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    for (string s; getline(cin, s);) {
        for (auto& x : s) {
            if (x == ' ') continue;
            for (int i {}; i < 4; ++i) {
                for (int j {}; j < 13; ++j) {
                    if (x == qwerty[i][j]) {
                        x = qwerty[i][j - 1];
                        goto out;
                    }
                }
            }
        out:;
        }
        cout << s << '\n';
    }
}
