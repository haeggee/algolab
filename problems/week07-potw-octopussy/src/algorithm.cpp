///
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

typedef pair<int, int> pd;

struct myComp {
    bool operator()(
        pd const& a,
        pd const& b)
    {
        return a.first < b.first;
    }
};

// return -1 if impossible to defuse, otherwise time it took;
// assume is_defused[j] is false
int defuse(int n, int curr_time, vector<int> &times, int j, vector<bool> &is_defused) {
  // cerr << j << endl;
  int t_j = times[j];
  if(j >= (n - 1) / 2) { // bombs at bottom
    if(curr_time < t_j) {
      is_defused[j] = true;
      return curr_time + 1;
    } else {
      return -1;
    }
  } else {
    int b1 = 2 * j + 1;
    int b2 = 2 * j + 2;
    if(!is_defused[b1]) {
      curr_time = defuse(n, curr_time, times, b1, is_defused);
    }
    if(curr_time == -1) {
      return -1;
    }
    if(!is_defused[b2]) {
      curr_time = defuse(n, curr_time, times, b2, is_defused);
    }
    if(curr_time == -1 || curr_time >= t_j) {
      return -1;
    } else {
      is_defused[j] = true;
      return curr_time + 1;
    }
  }
}

void testcase() {
  int n; cin >> n;
  vector<int> times(n);
  vector<pd> q(n);
  vector<bool> is_defused(n, false);

  for(int i = 0; i < n; i++) {
    cin >> times[i];
    q[i] = {times[i], i};
  }
  std::sort(q.begin(), q.end(), myComp());
  
  int curr_time = 0;
  for(int i = 0; i < n; i++) {
    int j = q[i].second;
    if(!is_defused[j]) {
      curr_time = defuse(n, curr_time, times, j, is_defused);
    }
    if(curr_time == -1) {
      cout << "no" << endl;
      return;
    }
  }
  cout << "yes" << endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t;
  while(t--) testcase();
}