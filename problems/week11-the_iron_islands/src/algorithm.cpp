#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

void testcase() {
    int n, k, w;
    std::cin >> n >> k >> w;
    std::vector<int> men(n);
    for(int i = 0; i < n; i++)
        std::cin >> men[i];

    std::vector<std::vector<int>> waterways(w);
    std::vector<std::vector<int>> waterways_prefix(w);
    for(int i = 0; i < w; i++) {
        int l; std::cin >> l;
        waterways[i] = std::vector<int>(l);
        waterways_prefix[i] = std::vector<int>(l);
        for(int j = 0; j < l; j++) {
            int r; std::cin >> r;
            waterways[i][j] = men[r];
            waterways_prefix[i][j] = j == 0 ? men[r] : men[r] + waterways_prefix[i][j-1];
        }
    }
    // first look for solution only inside single waterway via sliding window
    int max_interv = 0;

    // runtime O(n), because we visit every city at most twice (apart from city 0)
    for(int wi = 0; wi < w; wi++) {
        int i = 0, j = 0;
        int val = waterways[wi][0];
        int l = waterways[wi].size();
        while (j < l) {
            if (val < k) {
                j++;
                if (j == l) break;
                val += waterways[wi][j];
            } else {
                if (val == k) {
                    max_interv = std::max(max_interv, j - i + 1);   
                }
                val -= waterways[wi][i];
                i++;
                if (i > j) {
                    if (i == l) break;
                    j = i;
                    val = waterways[wi][i];
                }
            }
        }
    }

    typedef std::tuple<int,int,int> Path; // {prefix_sum, dist from 0, waterway i}
    std::vector<Path> paths;
    paths.reserve(n);
    for(int i = 0; i < w; i++) {
        for(int j = 1; j < waterways[i].size(); j++) {
            paths.emplace_back(waterways_prefix[i][j], j, i);
        }
    }

    std::sort(paths.begin(), paths.end(),
                [](const Path& e1, const Path& e2) -> bool {
                    return std::get<0>(e1) < std::get<0>(e2)
                        || (std::get<0>(e1) == std::get<0>(e2) && std::get<1>(e1) > std::get<1>(e2));
            });

    for(auto p : paths) {
        // std::cerr << "p: " << std::get<0>(p) << " " << std::get<1>(p) << " " << std::get<2>(p) << std::endl;
        int key = k - std::get<0>(p) + men[0];
        // std::cerr << "key: " << key << std::endl;
        auto first = paths.begin();
        auto last = paths.end();      
        auto el = std::lower_bound(first, last, std::tuple<int,int,int>({key, 0, 0}), 
                [](const Path& e1, const Path& e2) -> bool {
                    return std::get<0>(e1) < std::get<0>(e2);
                        // || (std::get<0>(e1) == std::get<0>(e2) && std::get<1>(e1) > std::get<1>(e2));
            });
        // std::cerr << "el: " << std::get<0>(*el) << " " << std::get<1>(*el) << " " << std::get<2>(*el) << std::endl;
        if(el != last && std::get<0>(*el) == key) {
            if(std::get<2>(*el) != std::get<2>(p)) {
                max_interv = std::max(max_interv, (std::get<1>(*el)) + std::get<1>(p) + 1);
            } else {
                el++;
                if(el != last && std::get<0>(*el) == key) {
                    max_interv = std::max(max_interv, (std::get<1>(*el)) + std::get<1>(p) + 1);
                }
            }
        }
    }
    std::cout << max_interv << std::endl;
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
