#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    auto counter = [i = 0]() mutable { return i++; };
    auto clock1 = counter;
    auto clock2 = counter;

    cout << clock1() << ' ' << clock1() << ' ' << clock1() << '\n';
    cout << clock2() << ' ' << clock2() << ' ' << clock2() << '\n';
}
