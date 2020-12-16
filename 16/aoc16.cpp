#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

std::vector<std::string> where_invalid(int val, std::map<std::string, std::array<int, 4>>& rules) {
  std::vector<std::string> invalids = {};
  for (auto const& [key, rule] : rules){
    bool curr_valid =
      (((val >= rule[0]) & (val <= rule[1])) |
       ((val >= rule[2]) & (val <= rule[3])));
    if (not curr_valid){
      // std::cout << val << " invalid in " << key << std::endl;
      invalids.push_back(key);
    }
  }
  return invalids;
}

std::vector<int> fetch_numbers(std::string line) {
  std::vector<int> out = {};
  int curr_ind = 0;
  int N = line.size();
  while (curr_ind < N) {
    int next_ind = line.find(',', curr_ind);
    std::string item;
    if (next_ind != -1) {
      item = line.substr(curr_ind, next_ind - curr_ind);
    } else {
      item = line.substr(curr_ind, N - curr_ind);
    }
    out.push_back(std::stoi(item));
    curr_ind += item.size() + 1;
  }
  return out;
}

int main() {

  //  Terrible approach to getting input
  std::string line;
  std::getline(std::cin, line);
  std::map<std::string, std::array<int, 4>> rules;

  while (line.size() > 0){
    int colon_loc = line.find(':');
    std::string rule = line.substr(0, colon_loc);
    int or_loc = line.find(" or ");
    int first_dash = line.find_first_of('-');
    int second_dash = line.find_last_of('-');
    std::array<int, 4> rule_lims;
    std::string r0 = line.substr(colon_loc + 2, first_dash - colon_loc-2);
    rule_lims[0] = std::stoi(r0);
    std::string r1 = line.substr(first_dash + 1, or_loc - first_dash-1);
    rule_lims[1] = std::stoi(r1);
    std::string r2 = line.substr(or_loc + 4, second_dash - or_loc - 4);
    rule_lims[2] = std::stoi(r2);
    std::string r3 = line.substr(second_dash + 1, line.size() - second_dash);
    rule_lims[3] = std::stoi(r3);
    rules[rule] = rule_lims;
    std::getline(std::cin, line);
  }
  std::getline(std::cin, line); // your ticket:
  std::getline(std::cin, line);
  std::vector<int> my_ticket = fetch_numbers(line);
  std::getline(std::cin, line);
  std::getline(std::cin, line); // nearby tickets:

  // Collect all valid tickets and part 1 solution
  std::vector<std::vector<int>> valid_tickets;
  int invalids_sum = 0;
  for (std::string nearby_line;std::getline(std::cin, nearby_line);) {
    std::vector<int> current_ticket = fetch_numbers(nearby_line);
    // std::cout << nearby_line << std::endl;
    bool all_valid = true;
    for (auto val : current_ticket){
      std::vector<std::string> invalids = where_invalid(val, rules);
      if (invalids.size() == rules.size()){
        invalids_sum += val;
      }
      all_valid &= (invalids.size() < rules.size());
    }
    if (all_valid) {
      valid_tickets.push_back(current_ticket);
    }
  }
  std::cout << "Part 1: " << invalids_sum << std::endl;

  std::map<std::string, std::set<int>> possible_locations;
  int ticket_size = valid_tickets[0].size();

  // Collect all valid ticket field locations
  for (auto const &[key, rule] : rules) {
    for (int i=0; i<ticket_size; i++){
      possible_locations[key].insert(i);
    }
  }
  std::set<int>::iterator it;
  for (auto valid_ticket : valid_tickets){
    for (int i=0; i < ticket_size; i++) {
      std::vector<std::string> invalids = where_invalid(valid_ticket[i], rules);
      for (auto invalid : invalids){
        it = possible_locations[invalid].find(i);
        if (it != possible_locations[invalid].end()){
          possible_locations[invalid].erase(it);
        }
      }
    }
  }

  // Iterate through ones that can only be in one place,
  // and remove those from all others.
  std::map<std::string, int> solution;
  while (solution.size() < rules.size()){
    std::string found;
    int found_loc;
    for (auto const& [key, locs]:possible_locations){
      if (locs.size() == 1){
        found_loc = *locs.begin();
        found = key;
        break;
      }
    }
    solution[found] = found_loc;
    possible_locations.erase(possible_locations.find(found));
    for (auto const& [key, plocs]: possible_locations){
      it = possible_locations[key].find(found_loc);
      if (it != possible_locations[key].end()) {
        possible_locations[key].erase(it);
      }
    }
  }

  // Get part 2 answer
  long total_starting_dep = 1;
  for (auto const &[key, l] : solution) {
    if (key.substr(0, 9) == "departure"){
      total_starting_dep *= my_ticket[l];
      std::cout << key << " at location: " << l << std::endl;
    }
  }
  std::cout << "Part 2: " << total_starting_dep << std::endl;
}
