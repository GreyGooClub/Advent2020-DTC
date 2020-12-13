#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::pair<bool, std::vector<long>> check(long N, std::vector<long> &scheds,
                                         std::vector<int> &offs) {
  bool correct = true;
  int Nsched = scheds.size();
  std::vector<long> goods = {};
  for (int i=0; i < Nsched; i++){
    if (((N + offs[i]) % scheds[i]) != 0) {
      correct = false;
    } else {
      goods.push_back(scheds[i]);
    }
  }
  return std::make_pair(correct, goods);
}

int main() {

  std::vector<long> vector_bus_ids;
  std::string timestamp_str;
  std::getline(std::cin, timestamp_str);
  long timestamp = std::stol(timestamp_str);
  std::string schedule_str;
  std::getline(std::cin, schedule_str);

  std::vector<long> schedules;
  std::vector<int> offsets;
  int curr_offset = 0;
  std::size_t curr_loc = 0;
  while (curr_loc < schedule_str.size()){
    int next_comma = schedule_str.find(',', curr_loc);
    std::string curr_str = schedule_str.substr(curr_loc, next_comma-curr_loc);
    if (curr_str != "x"){
      long value = std::stol(curr_str);
      schedules.push_back(value);
      offsets.push_back(curr_offset);
    }
    curr_offset++;
    if (next_comma < 0){
      break;
    }
    curr_loc = next_comma + 1;
  }

  // Part 1
  long min_time = schedules[0] - (timestamp % schedules[0]);
  long earliest_bus = schedules[0];
  int Nsched = schedules.size();

  for (int i=1; i < Nsched; i++){
    long time = schedules[i] - (timestamp % schedules[i]);
    if (time < min_time){
      min_time = time;
      earliest_bus = schedules[i];
    }
  }

  std::cout << "Part 1: " << earliest_bus * min_time << std::endl;

  // Part 2
  bool found = false;
  long curr_best = 0;
  long val = schedules[0];
  long curr_incr = 1;

  std::vector<long> found_arrangements = {};
  std::pair<bool, std::vector<long>> curr_result;

  while (not found) {
    curr_result = check(val, schedules, offsets);
    found = curr_result.first;
    found_arrangements = curr_result.second;
    if (found){
      break;
    }
    // insight is that the difference between a partial match and the
    // next better partial match is an integer multiple of the product
    // of the currently matching schedules.
    int num_found = found_arrangements.size();
    if (num_found > curr_best) {
      curr_best = num_found;
      long prod = 1;
      for (auto fa : found_arrangements) {
        prod *= fa;
      }
      curr_incr = prod;
    }
    val += curr_incr;
  }
  std::cout << "Part 2: " << val << std::endl;
}
