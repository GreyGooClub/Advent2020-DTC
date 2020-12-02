#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {


  std::size_t pol_sep;
  std::size_t range_sep;
  string password;
  string policy;
  char policy_char;
  std::size_t policy_lower;
  std::size_t policy_upper;
  string check_string_pt2;

  std::size_t num_req_chars;
  int num_valid_pt1 = 0;
  int num_valid_pt2 = 0;

  for (std::string line; std::getline(std::cin, line);){
    pol_sep = line.find(':');
    policy = line.substr(0, pol_sep);
    policy_char = policy[policy.size()-1];
    range_sep = policy.find('-');
    policy_lower = std::stoi(policy.substr(0, 2));
    policy_upper = std::stoi(policy.substr(range_sep+1, policy.size()));

    password = line.substr(pol_sep+2, line.size() - pol_sep -2);

    num_req_chars = std::count(password.begin(), password.end(), policy_char);

    // Part 1
    if ((num_req_chars >= policy_lower) && (num_req_chars <= policy_upper)){
      num_valid_pt1++;
    }

    // Part 2
    char check_char_array[] = {password[policy_lower-1], password[policy_upper-1]};
    check_string_pt2 = check_char_array;
    std::size_t valid_count_pt2 = std::count(check_string_pt2.begin(), check_string_pt2.end(), policy_char);

    if (valid_count_pt2 == 1){
        num_valid_pt2++;
      }
  }
  std::cout << "Number of valid entries (Part 1): " << num_valid_pt1 << std::endl;
  std::cout << "Number of valid entries (Part 2): " << num_valid_pt2 << std::endl;
}
