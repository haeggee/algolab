///
#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <limits>

int n, k, m;
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
typedef std::vector<VVI> VVVI;
typedef std::vector<VVVI> VVVVI;

struct Q
{
    int f1;
    int f2;
    int f3; // three previous fighters
};

struct key
{
    int i1;
    int i2;
    int i3;
};

int num_distinct(Q &q)
{
    // use the no_fighter = 0 to easily incorporate the min(m, q) constraint
    if (m == 2)
        return std::set<int>({0, q.f1, q.f2}).size() - 1;
    else
        return std::set<int>({0, q.f1, q.f2, q.f3}).size() - 1;
}

Q insert(Q &q, int val) // drops the last value f3
{
    return {val, q.f1, q.f2};
}

key encode(Q &north, Q &south, int diff) // return three indices, i1, i2, diff <= 24
{
    int k_n = 5 * north.f1 + north.f2;
    int k_s = 5 * south.f1 + south.f2;
    return {k_n, k_s, diff + 12};
}

int excitement(bool use_north, Q &north, Q &south, int diff)
{
    if (use_north)
        return (num_distinct(north) * 1000) - int(std::pow(2, std::abs(diff)));
    else
        return (num_distinct(south) * 1000) - int(std::pow(2, std::abs(diff)));
}

int solve(
    VVVVI &dp, int n, std::vector<int> &v, Q &north, Q &south, int diff)
{
    if (std::abs(diff) >= 12) // guaranteed to be negative value, so not feasible
    {
        return std::numeric_limits<int>::min();
    }
    if (n == -1)
        return 0;

    key k = encode(north, south, diff);
    if (dp[n][k.i1][k.i2][k.i3] != -1)
    {
        return dp[n][k.i1][k.i2][k.i3];
    }
    int f = v[n];
    Q new_north = insert(north, f);
    Q new_south = insert(south, f);
    // the excitement in this round for both choices
    int val_north = excitement(true, new_north, south, diff + 1);
    int val_south = excitement(false, north, new_south, diff - 1);

    int best = std::numeric_limits<int>::min();
    if (val_north >= 0)
    {
        best = val_north + solve(dp, n - 1, v, new_north, south, diff + 1);
    }
    if (val_south >= 0)
    {
        best = std::max(best, val_south + solve(dp, n - 1, v, north, new_south, diff - 1));
    }
    dp[n][k.i1][k.i2][k.i3] = best;
    return best;
}

void testcase()
{
    std::cin >> n >> k >> m;
    std::vector<int> v(n);

    VVVVI dp(n, VVVI(25, VVI(25, VI(25, -1))));
    for (int i = n - 1; i >= 0; --i)
    {
        std::cin >> v[i];
        v[i]++; // increase so that 0 is reserved for no fighter type
    }
    Q init_empty = {0, 0, 0};
    std::cout << solve(dp, n - 1, v, init_empty, init_empty, 0) << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false); // Always!
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++)
    {
        testcase();
    }
}