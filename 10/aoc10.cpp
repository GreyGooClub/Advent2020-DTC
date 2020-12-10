#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

int main() {

  std::vector<long> adaptors;
  adaptors.push_back(0);

  for (std::string line; std::getline(std::cin, line);){
    adaptors.push_back(std::stol(line));
  }

  long device_joltage = *std::max_element(adaptors.begin(), adaptors.end()) +  3;
  std::sort(adaptors.begin(), adaptors.end());
  adaptors.push_back(device_joltage);

  long current_joltage = 0;
  long one_jolt_jumps = 0;
  long three_jolt_jumps = 0;
  for (int i=1; i < adaptors.size(); i++){
    long diff = adaptors[i] - adaptors[i - 1];
    // std::cout << adaptors[i - 1] << " -> " << adaptors[i] << " : " << diff << std::endl;
    if (diff == 1) {
      one_jolt_jumps++;
    } else if (diff == 3){
      three_jolt_jumps++;
    }
  }

  std::cout << one_jolt_jumps << std::endl;
  std::cout << three_jolt_jumps << std::endl;

  std::cout << one_jolt_jumps*three_jolt_jumps << std::endl;

  long num_ways = 1;
  int ones_in_row = 0;

  for (int i = 1; i < adaptors.size(); i++) {
    long diff = adaptors[i] - adaptors[i - 1];
    if (diff == 1) {
      ones_in_row++;
    } else if (diff == 3) {
      if (ones_in_row != 0){
        int add = std::pow(2, ones_in_row-1) - (ones_in_row-1)/3;
        num_ways *= add;
        std::cout << ones_in_row << " " << add << " " << (ones_in_row-1) / 3 << " "
                  << num_ways << std::endl;
        ones_in_row = 0;
      }
    }
  }
  std::cout << num_ways << std::endl;
}
