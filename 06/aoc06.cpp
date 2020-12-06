#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

int main() {

  std::vector<std::string> all_lines;

  for (std::string line; std::getline(std::cin, line);) {
    all_lines.push_back(line);
  }

  int num_lines = all_lines.size();

  int line_index = 0;
  int total_yeses = 0;
  int total_shared_yeses = 0;

  while (line_index < num_lines) {
    bool end_of_entry = false;
    std::string current_entry;

    //  Gather entry across lines
    int num_people_in_group = 0;
    while (not end_of_entry) {
      std::string curr_line = all_lines[line_index];
      line_index++;
      current_entry += curr_line;
      if (curr_line.size() < 1) {
        end_of_entry = true;
      } else {
        num_people_in_group++; // if we're not an empty line, add a person
      }
    }
    // Construct set of questions answered yes
    std::set<char> answered_yes;
    for (auto ques : current_entry){
      answered_yes.emplace(ques);
    }
    total_yeses += answered_yes.size();

    // Identify how many elements of the set occur num_ps times.
    int all_answered_yes = 0;
    for (auto set_element : answered_yes){
      int num_occur = std::count(current_entry.begin(), current_entry.end(), set_element);
      if (num_occur == num_people_in_group) {
        all_answered_yes++;
      }
    }
    total_shared_yeses += all_answered_yes;
  }
  std::cout << "Total questions answered yes (Part 1): " << total_yeses << std::endl;
  std::cout << "Total questions all answered yes (Part 2): " << total_shared_yeses
            << std::endl;
}
