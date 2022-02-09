#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct sort_p {
  bool operator() (pair<int, int> t0, pair<int, int> t1) {
    return (t0.second < t1.second) ;
  }
};

void testcase() {
  int n; cin >> n;
  vector<pair<int, int>> boats(n);
  for(int i = 0; i < n; i++) {
    cin >> boats[i].first; cin >> boats[i].second;
  }
  std::sort(boats.begin(), boats.end(), sort_p());
  if(n == 1) {
    cout << 1 << endl;
  }
  int num_boats = 2;
  int l = boats[1].first;
  int p = boats[1].second;
  int previous_blocked = boats[0].second;
  int curr_blocked = max(previous_blocked + l, p);
  for(int i = 2; i < n; i++) {
    l = boats[i].first;
    p = boats[i].second;
    // cout << "l " << l << endl;
    // cout << "p " << p << endl;
    if(curr_blocked <= p - l) { // can put curr boat leftmost
      previous_blocked = curr_blocked;
      curr_blocked = p;
      num_boats++;
    } else if(curr_blocked <= p) { // can put boat at end of previous boat
      previous_blocked = curr_blocked;
      curr_blocked = curr_blocked + l;
      num_boats++;
    } else { 
      int taking_this_blocked = max(previous_blocked + l, p);
      if(taking_this_blocked < curr_blocked) { // can swap last boat with this one and go less with current blocking pos
        curr_blocked = taking_this_blocked; 
      }
    } 
  }

  cout << num_boats << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  while(t--) testcase();
}