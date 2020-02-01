#include <vector>
long long sum(std::vector<int>& a) {
    long long ans = 0;
    for (int x : a) ans += x;
    return ans;
}