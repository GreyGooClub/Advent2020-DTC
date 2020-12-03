#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int count_trees(std::vector<std::string> char_map, int slope_r, int slope_c){
  int num_rows = char_map.size();
  int num_cols = char_map[0].size();
  int num_trees = 0;
  int row = 0;
  int col = 0;
  while (row < num_rows && col < num_cols) {
    char current_char = char_map[row][col];
    if (current_char == '#') {
      num_trees++;
    }
    row += slope_r;
    col += slope_c;
    col = col % num_cols;
  }
  return num_trees;
}

int main() {

  std::vector<std::string> map;

  for (std::string line; std::getline(std::cin, line);){
    map.push_back(line);
  }

  std::cout << "Part 1: Trees encountered " << count_trees(map, 1, 3) << std::endl;

  std::vector<int> slopes_r = {1, 1, 1, 1, 2};
  std::vector<int> slopes_c = {1, 3, 5, 7, 1};
  int num_slopes = slopes_r.size();
  long trees_prod = 1;

  for (int i=0; i < num_slopes; i++){
    int num_trees = count_trees(map, slopes_r[i], slopes_c[i]);
    trees_prod *= num_trees;
  }
  std::cout << "Part 2: Trees encountered and multiplied " << trees_prod << std::endl;
}
