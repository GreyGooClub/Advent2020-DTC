#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>

long no_paren_solution(std::string line) {
  std::string result;
  std::vector<std::string> items;
  split(items, line, boost::is_any_of(" "), boost::token_compress_on);
  if (items.size() == 1) {
    return std::stol(items[0]);
  } else if (items[1] == "*") {
    result = std::to_string(std::stol(items[0]) * std::stol(items[2]));
  } else if (items[1] == "+") {
    result = std::to_string(std::stol(items[0]) + std::stol(items[2]));
  }
  items.erase(items.begin(), items.begin() + 3);
  items.insert(items.begin(), result);
  return no_paren_solution(boost::join(items, " "));
}

long no_paren_solution_ordered(std::string line) {
  std::string result;
  std::vector<std::string> items;
  split(items, line, boost::is_any_of(" "), boost::token_compress_on);
  auto it = std::find(items.begin(), items.end(), "+");
  int first_sum = std::distance(items.begin(), it);
  if (it == items.end()){
    return no_paren_solution(line);
  }
  result = std::to_string(std::stol(items[first_sum - 1]) +
                          std::stol(items[first_sum + 1]));
  items.erase(it-1, it + 2);
  items.insert(it-1, result);
  return no_paren_solution_ordered(boost::join(items, " "));
}

long full_solution(std::string problem,
                   long (*no_paren_func)(std::string line)) {
  int open_par = problem.find_first_of("(");
  if (open_par == std::string::npos){
    return no_paren_func(problem);
  } else {
    int close_par = open_par;
    int n_open = 1;
    while (n_open > 0){
      close_par++;
      if (problem[close_par] == ')'){
        n_open--;
      } else if (problem[close_par] == '('){
        n_open++;
      }
    }
    std::string inside_paren;
    inside_paren = problem.substr(open_par+1, close_par-open_par-1);
    std::string new_problem = problem;
    std::string solved_inside = std::to_string(full_solution(inside_paren, no_paren_func));
    new_problem.replace(open_par, close_par-open_par+1, solved_inside);
    return full_solution(new_problem, no_paren_func);
  }
}

int main() {

  long answer_pt1 = 0;
  long answer_pt2 = 0;

  for (std::string line; std::getline(std::cin, line);){
    long curr_sol_pt1 = full_solution(line, no_paren_solution);
    answer_pt1 += curr_sol_pt1;
    long curr_sol_pt2 = full_solution(line, no_paren_solution_ordered);
    answer_pt2 += curr_sol_pt2;
    // break;
  }
  std::cout << "Part 1: " << answer_pt1 << std::endl;
  std::cout << "Part 2: " << answer_pt2 << std::endl;
}
