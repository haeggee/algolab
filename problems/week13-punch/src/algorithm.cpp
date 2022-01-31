#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

int n, k;
struct sol {
    int c;
    int bev;
    bool use_i;
};

std::vector<std::vector<sol>> dp;

sol solve(int i, int k, std::vector<int> &cost, std::vector<int> &vol) {
    if(k <= 0) {
        return {0, 0, false};
    }
    if(i == 0) {
        int num = k / vol[i];
        num = k % vol[i] == 0 ? num : num + 1;
        // std::cerr << "k " << k << " i " << i << " vol " << vol[i] << " num " << num << std::endl;
        return {num * cost[i], 1, true};
    }
    if(dp[i][k].c != -1) {
        return dp[i][k];
    }

    // two options: take beverage _at least_ once or not at all
    
    // 1: don't take
    sol s1 = solve(i - 1, k, cost, vol);
    s1.use_i = false;
    // 2: take multiple times
    sol s2 = solve(i,  k - vol[i], cost, vol);
    s2.c += cost[i];
    sol best = s1;
    // order: 
    // 1: take minimal cost
    // 2: for same cost: more beverages
    // 3: for same cost and same beverages: 
    //    prefer if sol did not take beverage, i.e. we add one and are strictly higher
    // -- Q: why does s2.c < best.c || (s2.c == best.c && s2.bev >= best.bev) not give same answer?
    //       this means that we take beverage even if 
    if(s2.c < best.c || (s2.c == best.c && s2.bev > best.bev)
        || (s2.c == best.c && s2.bev == best.bev && !s2.use_i)) {
        best = {s2.c, s2.use_i ? s2.bev : s2.bev + 1, true};
    }

    dp[i][k] = best;
    return best;
}

void testcase() {
    std::cin >> n >> k;
    std::vector<int> cost(n);
    std::vector<int> vol(n);
    dp = std::vector<std::vector<sol>>(n, std::vector<sol>(k+1, {-1,0,false}));
    for(int i = 0; i < n; i++) {
        std::cin >> cost[i] >> vol[i];
    }

    sol s = solve(n-1, k, cost, vol);
    std::cout << s.c << " " << s.bev << std::endl;
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
