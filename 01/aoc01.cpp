#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

  int target_sum = 2020;
  std::vector<int> expenses;

  for (std::string line; std::getline(std::cin, line);){
    expenses.push_back(stoi(line));
  }
  std::sort(expenses.begin(), expenses.end());

  int current_upper;
  int current_lower;
  int N = expenses.size();

  // Double sum
  for (int i=0; i<N; i++){
    current_lower = expenses[i];
    for (int j=N-1; j > i; j--){
      current_upper = expenses[j];
      if ((current_upper + current_lower) == target_sum){
        std::cout << "Found double sum (then multiplied): " << (current_upper * current_lower) << std::endl;
      }
    }
  }

  // Triple sum
  int current_mid;
  for (int i=0; i < N; i++){
    current_lower = expenses[i];
    for (int j=N-1; j > i; j--){
      current_upper = expenses[j];
      for (int k=i; k < j; k++){
        current_mid = expenses[k];
        if ((current_upper + current_mid + current_lower) == target_sum){
          std::cout << "Found triple sum (then multiplied): " << (current_upper * current_mid * current_lower) << std::endl;
          return 0;
        }
      }
    }
  }
}
