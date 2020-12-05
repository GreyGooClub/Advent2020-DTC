#include <algorithm>
#include <cmath>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

int main() {

  int max = 0;
  std::vector<int> cids;

  for (std::string line; std::getline(std::cin, line);){
    int cid;
    int row = 0;
    for (int i = 0; i < 7; i++) {
      if (line[i] == 'B'){
        row += std::pow(2, 6-i);
      }
    }
    int col = 0;
    for (int i = 7; i < 10; i++) {
      if (line[i] == 'R') {
        col += std::pow(2, 9-i);
      }
    }
    cid = row*8 + col;
    cids.push_back(cid);
    if (cid > max){
        max = cid;
     }
    // std::cout << line << ' ' << row << ' ' << col << ' ' << cid << std::endl;
  }
  std::cout << "Highest ticket number (Part 1): " << max << std::endl;
  std::sort(cids.begin(), cids.end());

  for (std::size_t i=0; i<cids.size()-1; i++){
    int check = cids[i + 1] - cids[i];
    if (check> 1) {
      std::cout << "My seat (Part 2): " << cids[i]+1 << std::endl;
      break;
    }
  }
}
