#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>


struct A {
    int p;
    int h;
    int i;
};

struct B {
    int w;
    int i;
};

typedef std::vector<long> VL;
typedef std::vector<VL> VVL;
typedef std::vector<VVL> VVVL;

void testcase() {
    int n, m;
    long a, b, P, H, W;
    std::cin >> n >> m >> a >> b >> P >> H >> W;

    std::vector<A> pots_a(n);
    std::vector<B> pots_b(m);

    for(int i = 0; i < n; i++) {
        int p, h;
        std::cin >> p >> h;
        pots_a[i] = {p, h, i};
    }

    for(int i = 0; i < m; i++) {
        int w;
        std::cin >> w;
        pots_b[i] = {w, i};
    }
    // order of B potions is definite as they only have 1 unique val
    std::sort(pots_b.begin(), pots_b.end(), [](const B& b1, const B& b2) -> bool {
          return b1.w > b2.w;
            });

    // use long bc sum of powers can be larger than 2^32
    long l_min = std::numeric_limits<long>::min();
    VVVL dp(n + 1,  VVL(n + 1, VL(H + 1, l_min)));
    // dp[i][j][h] describes the maximum amount of power one can get
    // with the first i potions, using exactly j of them to have at least happiness h

    // init for using a single potions, just take the highest p over those that satisfy h
    for(int h = 0; h <= H; h++) {
        for(int i = 1; i <= n; i++) {
            dp[i][1][h] = dp[i-1][1][h];
            if(pots_a[i-1].h >= h && dp[i][1][h] < pots_a[i - 1].p)
                dp[i][1][h] = pots_a[i-1].p;
            // std::cerr << "i=" << i << " j=" << 1 << " h=" << h << " dp=" << dp[i][1][h] << std::endl;
        }
    }
    // std::cout << "--------------" << std::endl;
    for(int j = 2; j <= n; j++) {
        for(int h = 0; h <= H; h++) {
            for(int i = j; i <= n; i++) {
                // either take this one or take previous value
                int prev_h = std::max(0, h - pots_a[i-1].h);
                dp[i][j][h] = std::max(dp[i-1][j][h], dp[i-1][j-1][prev_h] + pots_a[i-1].p);
                // std::cerr << "i=" << i << " j=" << j << " h=" << h << " dp=" << dp[i][j][h] << std::endl;
            }
        }
    }

    int num_potions_a = -1;
    int num_potions_b = 0;
    long curr_wit = 0;
    // greedily take potions of B and try to find the _least_ number of potions A 
    // that together give us the power and wit
    for(; num_potions_b < m; num_potions_b++) {
        curr_wit += pots_b[num_potions_b].w;
        long neg_power = (num_potions_b + 1) * b;
        if(curr_wit >= W) {
            // curr_wit suffices to have W, look for smallest j that gives us all
            for(int j = 1; j <= n; j++) {
                if(curr_wit - j * a < W) {
                    break;
                }
                if(dp[n][j][H] >= P + neg_power) {
                    num_potions_a = j;
                    // std::cerr << num_potions_a << " " << num_potions_b + 1 << std::endl;
                    std::cout << num_potions_a + num_potions_b + 1 << std::endl;
                    return;
                }
            }
        }
    }
    
    if(num_potions_a == -1) {
        std::cout << -1 << std::endl;
        return;    
    }

    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
