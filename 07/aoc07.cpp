#include <bits/c++config.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

// Map of Parent : (Vector of children)
// Each element of the child vector is a pair of string and int
// (bag colour and number).
std::map<std::string, std::vector<std::pair<std::string, int>>> bag_rules;

// Maintain a cache of checked parents.
// Unclear if this is actually an optimisation
std::set<std::string> no_gold_children;

int traverse_to_gold(std::string bag_id){

  // Goal is to traverse downwards by calling this function
  // recursively on children. If gold found, we immediately
  // return all the way out. If not, we traverse the current
  // level of parents laterally with continues to be
  // explicit.

  for (auto child_pair : bag_rules[bag_id]){
    if (child_pair.first == "shiny gold"){
      return 1;                 //  Found gold, exit
    }
    else if (child_pair.second == 0) {
      // Child is leaf, traverse laterally
      continue;
    }
    else if (no_gold_children.find(child_pair.first) == no_gold_children.end()){
      // WE HAVE TO GO DEEPER (if not in cache)
      // Return if gold below, otherwise add to check cache and
      // traverse laterally
      if (traverse_to_gold(child_pair.first) == 1){
        return 1;
      } else {
        // Add to cache
        no_gold_children.emplace(child_pair.first);
        continue;
      }
    }
  }
  return 0;
}

int total_bags_inside(std::string bag_id) {
  long nbags = 0;               // Been burned by my buddy int before
  for (auto child_pair : bag_rules[bag_id]) {
    nbags += child_pair.second + child_pair.second*total_bags_inside(child_pair.first);
  }
  return nbags;
}

int main(){

  for (std::string line; std::getline(std::cin, line);) {
    // Start of what I could do in ~2 lines in python
    line.erase(line.find('.'));  // Fuck you period
    std::string bag_id = line.substr(0, line.find("contain")-1);
    bag_id = bag_id.substr(0, bag_id.find_last_of(' '));

    std::size_t curr_loc = line.find("contain") + 7;
    while (curr_loc < line.size()) {
      std::size_t end_curr = line.find(",", curr_loc);
      std::string rule = line.substr(curr_loc, end_curr - curr_loc);
      curr_loc += rule.size() + 1;
      std::string num_str = rule.substr(1, rule.find(' ', 1));
      int num;
      if (num_str == "no ") {
        num = 0;
      } else {
        num = std::stoi(num_str);
      }
      std::string bag_str = rule.substr(rule.find(' ', 1) + 1, -1);
      bag_str = bag_str.substr(0, bag_str.find_last_of(' '));
      std::pair<std::string, int> curr_pair(bag_str, num);
      bag_rules[bag_id].push_back(curr_pair);
      // End of what I could do in ~2 lines in python
    }
  }
  int num_gold_parents = 0;
  for (auto [bag_id, bag_rule] : bag_rules) {
    num_gold_parents += traverse_to_gold(bag_id);
  }
  std::cout << "Answer part 1: " << num_gold_parents << std::endl;
  std::cout << "Answer part 2: " << total_bags_inside("shiny gold") << std::endl;
}
