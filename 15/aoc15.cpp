#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

std::vector<int> fetch_numbers(std::string line){
  std::vector<int> out = {};
  int curr_ind = 0;
  int N = line.size();
  while (curr_ind < N){
    int next_ind = line.find(',', curr_ind);
    std::string item;
    if (next_ind != -1) {
      item = line.substr(curr_ind, next_ind-curr_ind);
    }
    else {
      item = line.substr(curr_ind, N-curr_ind);
    }
    out.push_back(std::stoi(item));
    curr_ind += item.size()+1;
  }
  return out;
}

int main() {

  for (std::string line; std::getline(std::cin, line);){
    std::vector<int> input_numbers = fetch_numbers(line);
    int Ninput = input_numbers.size();

    auto lookup = new int[30000000][2];
    // times spoken, when spoken last

    for (int i = 0; i < Ninput; i++) {
      lookup[input_numbers[i]][0] = 1;
      lookup[input_numbers[i]][1] = i;
    }
    int last_spoken = input_numbers[Ninput-1];

    int index = Ninput;
    int previous_index = index; // When last_spoken number was spoken last previously
    int say;

    int Nturns = 30000000;
    // int Nturns = 2020;
    int max_num = 0;

    while (index < Nturns) {
      if (last_spoken > max_num){
        max_num = last_spoken;
      }
      if (lookup[last_spoken][0] == 1) { // Was first time said
        say = 0;
      } else {
        say = (index-1) - previous_index;
      }
      lookup[say][0]++;
      previous_index = lookup[say][1];
      lookup[say][1] = index;
      last_spoken = say;
      index++;
    }
    std::cout << last_spoken << std::endl;
    std::cout << max_num << std::endl;
    delete [] lookup;
    break;
  }
}

