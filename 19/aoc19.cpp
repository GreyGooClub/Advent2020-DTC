#include <boost/algorithm/string/replace.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <map>
#include <regex>

using namespace std;

int main() {

  map<int, string> rules;

  for (string line; getline(cin, line);){
    if (line.size()==0){
      break;
    } else {
      int colon = line.find(':');
      int rule_id = stoi(line.substr(0, colon));
      string curr_rule_str = line.substr(colon+2, line.size() - colon);
      if (curr_rule_str[0] == '"'){
        rules[rule_id] += curr_rule_str[1];
      } else{
        vector<string> items;
        string regex_rule = "(";
        boost::split(items, curr_rule_str, boost::is_any_of(" "));
        for (auto op : items){
          if (op != "|"){
            regex_rule += "[" +op+"]";
          } else {
            regex_rule += op;
          }
        }
        regex_rule += ")";
        rules[rule_id] = regex_rule;
      }
    }
  }

  regex rule_loc ("\\[\\d+\\]");
  string final_regex_part1 = rules[0];
  smatch sm;
  regex_search(final_regex_part1, sm, rule_loc);

  while (sm.size() > 0){
    string found = sm[0];
    int replace_rule = stoi(found.substr(1, found.size()-2));
    string replace = rules[replace_rule];
    boost::replace_all(final_regex_part1, found, replace);
    regex_search(final_regex_part1, sm, rule_loc);
    // cout << final_regex_part1 << endl;
  }

  regex bigre_part1 (final_regex_part1);

  string final_regex_part2 = rules[0];
  regex_search(final_regex_part2, sm, rule_loc);

  int max_loops = 5;
  int num_loops_11 = 0;
  int num_loops_8 = 0;

  while (sm.size() > 0) {
    string found = sm[0];
    int replace_rule = stoi(found.substr(1, found.size() - 2));
    string replace = rules[replace_rule];
    if (replace_rule == 11) {
      if (num_loops_11 < max_loops) {
        replace = "([42][31]|[42][11][31])";
        num_loops_11++;
      } else {
        replace = "([42][31])";
      }
    }
    if (replace_rule == 8) {
      if (num_loops_8 < max_loops) {
        replace = "([42]|[42][8])";
        num_loops_8++;
      } else {
        replace = "[42]";
      }
    }
    boost::replace_all(final_regex_part2, found, replace);
    regex_search(final_regex_part2, sm, rule_loc);
  }

  regex bigre_part2 (final_regex_part2);

  int count_matches_part1 = 0;
  int count_matches_part2 = 0;
  // Process messages
  for (string line; getline(cin, line);) {
    // cout << line << endl;
    // This only returns true if matches whole line.
    if (regex_match(line, bigre_part1)){
      count_matches_part1++;
    }
    if (regex_match(line, bigre_part2))
      count_matches_part2++;
  }
  cout << "Part 1: " << count_matches_part1 << endl;
  cout << "Part 2: " << count_matches_part2 << endl;
}
