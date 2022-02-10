#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

struct edge
{
    int v;
    int l;
};

struct result
{
    long coins;
    long num_nodes;
    long traversal_time; // time it takes to go from u to all nodes under v and come back
};

std::vector<result> dp;

typedef std::vector<std::vector<edge>>
    Edges;

result solve(int i, std::vector<long> &galleon, Edges &edges)
{
    if (edges[i].size() == 0)
    { // leaf
        // dp[i] = {galleon[i], 1, 0};
        return {galleon[i], 1, 0};
    }

    std::vector<result> rec_results;
    rec_results.reserve(edges[i].size());
    for (auto e : edges[i])
    {
        result res = solve(e.v, galleon, edges);
        // loose l coins for each node
        rec_results.push_back({res.coins - res.num_nodes * e.l, res.num_nodes, res.traversal_time + 2 * e.l});
    }

    std::sort(rec_results.begin(), rec_results.end(), [](const result &r1, const result &r2) -> bool
              { return r1.traversal_time * r2.num_nodes < r2.traversal_time * r1.num_nodes; });

    long total_coins = galleon[i];
    long num_nodes = 0;
    long traversal_time = 0;
    for(auto r : rec_results) {
        // std::cout << i << " " << r.coins << " " <<  r.num_nodes << " " << " " << r.traversal_time << std::endl;
        total_coins += r.coins - traversal_time * r.num_nodes;
        num_nodes += r.num_nodes;
        traversal_time += r.traversal_time;
    }
    // std::cout << "result: " << i << " " << total_coins << " " <<  num_nodes << " " << " " << traversal_time << std::endl;   
    return {total_coins, num_nodes + 1, traversal_time} ; // return max_reward without taking current time into account
}

void testcase()
{
    int n;
    std::cin >> n;
    std::vector<long> galleon(n + 1);
    Edges edges(n + 1);
    dp = std::vector<result>(n + 1);
    for (int i = 0; i < n; i++)
    {
        std::cin >> galleon[i + 1];
    }

    for (int i = 0; i < n; i++)
    {
        int u, v, l;
        std::cin >> u >> v >> l;
        edges[u].push_back({v, l});
    }

    std::cout << solve(0, galleon, edges).coins << std::endl;
    return;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
