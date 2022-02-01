#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

std::vector<long> galleons;
std::vector<std::vector<std::pair<long, long>>> adj;
//value, num_nodes, execution_time
std::vector<std::vector<long>> tuples;
std::vector<std::pair<long, long>> storage;

void recurse(int current) {
	if(adj[current].size() == 0) {
		tuples[current][0] = galleons[current];
		tuples[current][1] = 1;
		tuples[current][2] = 0;
		return;
	}
	long total = 0;
	int num_children = 0;
	tuples[current][1] = 1;
	tuples[current][0] = galleons[current];
	for(std::pair<long, long> nei : adj[current]) {
		recurse(nei.first);		
	}
	for(std::pair<long, long> nei : adj[current]) {
		tuples[nei.first][0] -= tuples[nei.first][1] * nei.second;
		tuples[current][1] += tuples[nei.first][1];
		tuples[nei.first][2] += 2 * nei.second;
		total += tuples[nei.first][2];
		storage[num_children++] = std::make_pair(tuples[nei.first][1], tuples[nei.first][2]);
		tuples[current][0] += tuples[nei.first][0];
	}
	tuples[current][2] = total;
	std::sort(storage.begin(), storage.begin() + num_children, [](std::pair<long, long> a, std::pair<long, long> b){return a.first * b.second > a.second * b.first;});	
	int running_children = tuples[current][1] -1;
	for(int i = 0; i < num_children-1; i++) {
		running_children -= storage[i].first;
		tuples[current][0] -= running_children * storage[i].second;
	}
}

void testcase() {
	int n; std::cin >> n;

	galleons = std::vector<long>(n+1);
	storage = std::vector<std::pair<long, long>>(n);
	adj = std::vector<std::vector<std::pair<long, long>>>(n+1, std::vector<std::pair<long, long>>());
	tuples = std::vector<std::vector<long>>(n+1, std::vector<long>(3, -1));

	for(int i = 0; i < n; i++) {
		std::cin >> galleons[i+1];
	}

	for(int i = 0; i < n; i++) {
		long u, v, l; std::cin >> u >> v >> l;
		adj[u].push_back(std::make_pair(v, l));
	}
	recurse(0);
	std::cout << tuples[0][0] << std::endl;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t; std::cin >> t;

	for(int i = 0; i < t; i++) testcase();

	return 0;
}