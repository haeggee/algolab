///
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>

using namespace std;

void testcase() {
  int n; cin >> n;
  int m; cin >> m;
  int max_strength = 0;
  int max_weight = 0;
  vector<int> strength(n);
  vector<int> weight(m);
  for(int i = 0; i < n; i++) {
    cin >> strength[i];
    max_strength = max(max_strength, strength[i]);
  }
  for(int i = 0; i < m; i++) {
    cin >> weight[i];
    max_weight = max(max_weight, weight[i]);
  }
  
  if(max_weight > max_strength) {
    cout << "impossible" << endl;
    return;
  }
  
  std::sort(strength.begin(), strength.end(), std::greater<>());
  
  /* master solution
  int max_num_boxes = 0;
  multiset<int, std::greater<>> weights_set;
  for(int i = 0; i < m; i++) 
    weights_set.insert(weight[i]);
  
  while(!weights_set.empty()) {
    max_num_boxes++;
    for(int i = 0; i < n; i++) {
      auto b = weights_set.lower_bound(strength[i]);
      if(b != weights_set.end()) {
        weights_set.erase(b);
      } else {
        break;
      }
    }
  }
  */
  
  // My solution
  std::sort(weight.begin(), weight.end(), std::greater<>());
  vector<int> num_boxes(n, 0);
  int max_num_boxes = 1;
  num_boxes[0] = 1; // start with first guy carrying heaviest box
  for(int i = 1; i < m; i++) {
    int weight_i = weight[i];
    // the index of the _last_ guy that is next in line to carry it
    auto next = std::upper_bound(num_boxes.begin(), num_boxes.end(), max_num_boxes, std::greater<>());
    // the index of the first guy that is _too weak_ to carry it
    auto end = std::upper_bound(strength.begin(), strength.end(), weight_i, std::greater<>());
    int next_index = next - num_boxes.begin();
    int end_index = end - strength.begin();
    // cerr << i << " " << next_index << " " << end_index << endl;
    if(next_index < end_index) {
      num_boxes[next_index]++;
    } else {
      num_boxes[0]++;
      max_num_boxes = num_boxes[0];
    }
  }
  
  int min_time = (max_num_boxes - 1) * 3 + 2;
  cout << min_time << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  while(t--) testcase();
}