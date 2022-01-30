#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

struct move
{
    long d;
    long t;
};

bool subsetsum_rec(int i, std::vector<move> &elements, long D, long T)
{
    if (D <= 0 && T > 0)
        return true;
    if ((i == 0 && D > 0) || i < 0 || T < 0)
        return false;
    return subsetsum_rec(i - 1, elements, D - elements[i - 1].d, T - elements[i - 1].t) || subsetsum_rec(i - 1, elements, D, T);
}

bool subsetsum_iter(int n, std::vector<move> &elements, long D, long T)
{
    for (int s = 0; s < 1 << n; ++s)
    { // Iterate through all subsets
        long sum_D = 0;
        long sum_T = 0;
        for (int i = 0; i < n; ++i)
        {
            if (s & 1 << i)
            {
                sum_D += elements[i].d; // If i-th element in subset
                sum_T += elements[i].t;
            }
        }
        if (sum_D >= D && sum_T < T)
            return true;
    }
    return false;
}

bool split_list(int n, std::vector<move> &elements, long D, long T)
{
    int n1 = n / 2;
    int n2 = n - n1;

    std::vector<move> subsums1;
    std::vector<move> subsums2;

    // first fill the subset sums of set n1
    for (int s = 0; s < 1 << n1; ++s)
    { // Iterate through all subsets
        long sum_D = 0;
        long sum_T = 0;
        for (int i = 0; i < n1; ++i)
        {
            if (s & 1 << i)
            {
                sum_D += elements[i].d; // If i-th element in subset
                sum_T += elements[i].t;
            }
        }
        if (sum_D >= D && sum_T < T)
            return true;
        if (sum_T < T)
            subsums1.push_back({sum_D, sum_T});
    }

    // then fill subset sums of set n2
    for (int s = 0; s < 1 << n2; ++s)
    { // Iterate through all subsets
        long sum_D = 0;
        long sum_T = 0;
        for (int i = 0; i < n2; ++i)
        {
            if (s & 1 << i)
            {
                sum_D += elements[n1 + i].d; // If i-th element in subset
                sum_T += elements[n1 + i].t;
            }
        }
        if (sum_D >= D && sum_T < T)
            return true;
        if (sum_T < T)
            subsums2.push_back({sum_D, sum_T});
    }
    
    std::sort(subsums2.begin(), subsums2.end(), [](const move &m1, const move &m2) -> bool
              { return m1.t > m2.t; });
    
    // important step! when doing the binary search, we look for the _largest_ t that still
    // fits into sum < T, but we want to maximize the sum D.
    // hence, copy over the max D for which t' < t
    for (int i = subsums2.size() - 2; i >= 0; i--)
    {
        subsums2[i].d = std::max(subsums2[i + 1].d, subsums2[i].d);
    }

    for (auto m1 : subsums1)
    {
        move key = {D - m1.d, T - m1.t};
        // we look for first one that is __greater__ (because T is a hard constraint, no eq)
        // --> use upper bound, not lower_bound
        auto p = std::upper_bound(subsums2.begin(), subsums2.end(), key, [](const move &m1, const move &m2) -> bool
                                  { return m1.t > m2.t; });
        if (p != subsums2.end() && (m1.d + p->d >= D) && m1.t + p->t < T)
            return true;
    }

    return false;
}

void testcase()
{
    int n, m;
    long D, T;
    std::cin >> n >> m >> D >> T;
    std::vector<move> moves(n);
    for (int i = 0; i < n; i++)
    {
        long d, t;
        std::cin >> d >> t;
        moves[i] = {d, t};
    }

    std::vector<long> s(m);
    for (int i = 0; i < m; i++)
    {
        std::cin >> s[i];
    }

    int l = 0, r = m - 1;
    if (split_list(n, moves, D, T))
    {
        std::cout << 0 << std::endl;
        return;
    }

    while (l <= r)
    {
        int mid = (l + r) / 2;
        for (int i = 0; i < n; i++)
        {
            moves[i].d += s[mid];
        }

        if (split_list(n, moves, D, T))
        {
            r = mid;
            if (l == r)
                break;
        }
        else
        {
            l = mid + 1;
        }
        for (int i = 0; i < n; i++)
        {
            moves[i].d -= s[mid];
        }
    }

    if (l < m)
        std::cout << l + 1 << std::endl;
    else
        std::cout << "Panoramix captured" << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
