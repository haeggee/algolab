///2
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;

void testcase() {
  int n; cin >> n; // Read the number of integers to follow
  VI v(n);
  for(int i = 0; i < n; i++) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());
  int i = 0;
  int j = 0;
  int max_num_par = 0;
  int min_long_dist = 101;
  vector<int> positions;
  
  while (j < n) {
    // cout << "i " << i << "  j " << j << endl;
    if(v[j] - v[i] <= 200) { // parasols betw. i and j can be covered
      if(j - i + 1 > max_num_par) { // new best
        // cout << "here" << endl;
        positions.clear();
        max_num_par = j - i + 1;
        int pos = v[i] + (v[j] - v[i]) / 2;
        positions.push_back(pos);
        if((v[i] + v[j]) % 2 == 0) {
          min_long_dist = pos - v[i];
        } else {
          positions.push_back(pos + 1);
          min_long_dist = pos + 1 - v[i];
        }
      } else if(j - i + 1 == max_num_par) { // same num. parasols
        int pos = v[i] + (v[j] - v[i]) / 2;
        int this_long_dist = (v[i] + v[j]) % 2 == 0 ? pos - v[i] : pos - v[i] + 1;
        if(this_long_dist <= min_long_dist) {
          if(this_long_dist < min_long_dist) {
            positions.clear();
            min_long_dist = this_long_dist;
          }
          positions.push_back(pos);
          if((v[i] + v[j]) % 2 != 0) {
            positions.push_back(pos + 1);
          }
        }
      }
      j++; // grow sliding window
    } else {
      i++;
      if (i > j) {
        // if (i == n) break;
        j = i;
      }
    }
  }
  cout << max_num_par <<  " " << min_long_dist << endl;
  for(int i : positions) {
    cout << i << " ";
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false); // Always!
  int t; cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
