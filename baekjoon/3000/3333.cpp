#include <bits/stdc++.h>

constexpr auto TAU = 2 * M_PI;

struct Event {
    double angle;
    int add;
    Event(double angle, int add) : angle(angle), add(add) {}
};

int main(int argc, char** argv) {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    vector<int> x(n), y(n);
    for (int i {}; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    vector<Event> events;
    events.reserve(n << 2);
    auto f = [&](double mid) -> pair<double, double> {
        for (int i {}; i < n; ++i) {
            events.clear();
            for (int j {}; j < n; ++j) {
                if (i == j) continue;
                const auto dist {hypot(x[j] - x[i], y[j] - y[i])};
                if (dist > 2 * mid) continue;
                const auto angle {atan2(y[j] - y[i], x[j] - x[i])};
                const auto delta {acos(dist / 2 / mid)};
                events.emplace_back(angle - delta, 1);
                events.emplace_back(angle + delta, -1);
                events.emplace_back(angle - delta + TAU, 1);
                events.emplace_back(angle + delta + TAU, -1);
            }
            sort(events.begin(), events.end(), [&](const auto& lhs, const auto& rhs) {
                return lhs.angle < rhs.angle;
            });
            auto cnt {1};
            for (const auto& [angle, add] : events) {
                if ((cnt += add) == k) {
                    return {x[i] + mid * cos(angle), y[i] + mid * sin(angle)};
                }
            }
        }
        return {DBL_MAX, DBL_MAX};
    };
    auto lo {0.0}, hi {10000.0};
    while (hi - lo > 1e-4) {
        const auto mid {(lo + hi) / 2};
        (f(mid).first == DBL_MAX ? lo : hi) = mid;
    }
    const auto cen {f(hi)};
    cout << fixed << setprecision(9)
         << hi << '\n'
         << cen.first << ' ' << cen.second << '\n';
}
