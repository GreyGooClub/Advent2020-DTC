#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int main() {

  std::vector<int> cids;

  // Read in and part 1
  for (std::string line; std::getline(std::cin, line);){
    int cid = 0;
    int N = line.size();
    for (int i=0; i < N; i++) {
      if ((line[i] == 'B') || (line[i] == 'R')){
        cid += std::pow(2, N-1-i);
      }
    }
    cids.push_back(cid);
  }

  int max = *std::max_element(cids.begin(), cids.end());
  std::cout << "Highest ticket number (Part 1): " << max << std::endl;

  // Part 2
  std::sort(cids.begin(), cids.end());
  for (std::size_t i=0; i < cids.size()-1; i++){
    int check = cids[i + 1] - cids[i];
    if (check> 1) {
      std::cout << "My seat (Part 2): " << cids[i]+1 << std::endl;
      break;
    }
  }
}
