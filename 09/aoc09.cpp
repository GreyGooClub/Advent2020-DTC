#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

  std::vector<long> vector_of_longs;

  for (std::string line; std::getline(std::cin, line);){
    vector_of_longs.push_back(std::stol(line));
  }

  int len_preamble = 25;
  long invalid;
  int length = vector_of_longs.size();

  for (int i=len_preamble; i< length; i++){
    bool found_sum = false;
    for (int j=i-len_preamble; j < i; j++){
      for (int k = i-len_preamble; k < i; k++)
        if (k != j){
          long sum = vector_of_longs[k] + vector_of_longs[j];
          if (sum == vector_of_longs[i]){
            found_sum = true;
          }
        }
    }
    if (not found_sum){
      invalid = vector_of_longs[i];
      std::cout << "Part 1: " << invalid << std::endl;
      break;
    }
  }

  // Part 2
  for (int i = 0; i < length; i++) {
    long curr_sum = 0;
    int j = 0;
    std::vector<long> contig_range;
    while ((curr_sum < invalid) && ((i+j) < length)){
      curr_sum += vector_of_longs[i+j];
      contig_range.push_back(vector_of_longs[i+j]);
      j++;
    }
    if ((curr_sum == invalid) && (contig_range.size() > 1)){
      long max = *std::max_element(contig_range.begin(), contig_range.end());
      long min = *std::min_element(contig_range.begin(), contig_range.end());
      std::cout << "Part 2: " << min + max << std::endl;
      break;
    }
  }
}
