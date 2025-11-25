#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>
#include <iomanip>
// ...existing code...
#include <random>
// ...existing code...

using namespace std;

// y = log(2 * log(m*n)) + 0.1 * log(m*n)
// Uses natural logarithm (std::log). m*n must be > 1 for inner log > 0.
double computeY(double m, double n)
{
    double prod = m * n;
    double inner = std::log(prod); // log(m*n)
    return std::log(2.0 * inner) + 0.1 * inner;
}

// (Optional) base-10 version if needed:
// y = log10(2 * log10(m*n)) + 0.1 * log10(m*n)
double computeY_base10(double m, double n)
{
    double prod = m * n;
    double inner = std::log10(prod);
    return std::log10(2.0 * inner) + 0.1 * inner;
}

// ...existing code...

// y_noisy = scale * computeY(m,n) + noise, where noise ~ N(0, (relStd*|scaled_y|)^2)
// and |noise| is capped to maxAbsFrac*|scaled_y| (default 15%).
double computeY_noisy(double m, double n, double relStd = 0.05, double maxAbsFrac = 0.15, double scale = 1.58)
{
    double y = scale * computeY(m, n); // scale first
    double ay = std::abs(y);
    double sigma = relStd * ay;
    if (sigma == 0.0)
        return y;

    static thread_local std::mt19937_64 rng(std::random_device{}());
    std::normal_distribution<double> dist(0.0, sigma);

    double noise = dist(rng);
    double cap = maxAbsFrac * ay;
    noise = std::clamp(noise, -cap, cap); // ensure |noise| <= 15% of |scaled y|
    return y + noise;
}

// ...existing code...
int main()
{
    double m = 3.0;
    vector<int> bases = {1, 4, 8, 16, 32, 64, 128, 256};
    cout << fixed << setprecision(12);
    for (int b : bases)
    {
        double n = std::sqrt(b);
        double y = computeY(m, n);
        double y_noisy = computeY_noisy(m, n); // uses 1.58 scaling internally
        cout << "base=" << b
             << " n=" << n
             << " y=" << y
             << " y_noisy_scaled=" << y_noisy << '\n';
    }
    return 0;
}

// int main()
// {
//     double m = 5.0;
//     vector<int> bases = {1, 4, 8, 16, 32, 64, 128, 256};
//     cout << fixed << setprecision(12);
//     for (int b : bases)
//     {
//         double n = std::sqrt(b);
//         double y = computeY(m, n);
//         cout << "base=" << b << " n=" << n << " y=" << y << '\n';
//     }
//     return 0;
// }