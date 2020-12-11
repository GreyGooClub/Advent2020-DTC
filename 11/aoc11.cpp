#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
 
int main() {

  std::vector<std::string> vector_of_strings;

  for (std::string line; std::getline(std::cin, line);){
    vector_of_strings.push_back(line);
  }

  int Nrow = vector_of_strings.size();
  int Ncol = vector_of_strings[0].size();

  char seat_array[Nrow][Ncol];

  for (int i=0; i < Nrow; i++){
    for (int j=0; j < Ncol; j++){
      seat_array[i][j] = vector_of_strings[i][j];
    }
  }

  std::vector<int> adjacency_row = {
    -1, -1, -1,
     0,      0,
     1,  1,  1,
  };
  std::vector<int> adjacency_col = {
    -1, 0, 1,
    -1,    1,
    -1, 0, 1
  };

  // Part 1
  bool changed = true;
  while (changed){
  // int count = 0;
  // while (count < 10){
    changed = false;
    char new_seat_array[Nrow][Ncol];

    for (int i=0; i < Nrow; i++){
      for (int j=0; j < Ncol; j++){
        std::string adjacent;
        for (int k=0; k < 8; k++){
          int curr_i = i + adjacency_row[k];
          int curr_j = j + adjacency_col[k];
          if ((curr_i < 0) || (curr_j < 0) ||
              (curr_i >= Nrow) || (curr_j >= Ncol)) {
            continue;
          } else {
            adjacent.push_back(seat_array[curr_i][curr_j]);
          }
        }
        int adjacent_occupied = std::count(adjacent.begin(), adjacent.end(), '#');
        int adjacent_empty = std::count(adjacent.begin(), adjacent.end(), 'L');
        // Seat empty and no seats
        if ((seat_array[i][j] == 'L') && (adjacent_occupied==0)){
          changed = true;
          new_seat_array[i][j] = '#';
        } else if ((seat_array[i][j] == '#') && (adjacent_occupied >= 4)) {
          // Occupied and shy
          changed = true;
          new_seat_array[i][j] = 'L';
        } else {
          new_seat_array[i][j] = seat_array[i][j];
        }
        // std::cout << adjacent << std::endl;
      }
    }
    //  Apply changes
    for (int i = 0; i < Nrow; i++) {
      for (int j = 0; j < Ncol; j++) {
        seat_array[i][j] = new_seat_array[i][j];
      }
    }
  }

  int count_part1 = 0;
  for (int i = 0; i < Nrow; i++) {
      for (int j = 0; j < Ncol; j++) {
        if (seat_array[i][j] == '#') {
          count_part1++;
        }
      }
    }
  std::cout << count_part1 << std::endl;

  // Reset array
  for (int i = 0; i < Nrow; i++) {
    for (int j = 0; j < Ncol; j++) {
      seat_array[i][j] = vector_of_strings[i][j];
    }
  }

  // Part 2
  changed = true;
  while (changed){
    changed = false;
    char new_seat_array[Nrow][Ncol];

    for (int i=0; i < Nrow; i++){
      for (int j=0; j < Ncol; j++){
        std::string adjacent;
        for (int k=0; k < 8; k++){
          int count_path = 1;
          bool found_or_edge = false;
          while (not found_or_edge){
            int curr_i = i + adjacency_row[k]*count_path;
            int curr_j = j + adjacency_col[k]*count_path;
            if ((curr_i < 0) || (curr_j < 0) ||
                (curr_i >= Nrow) || (curr_j >= Ncol)) {
              found_or_edge = true;
            } else if (seat_array[curr_i][curr_j] != '.'){
              adjacent.push_back(seat_array[curr_i][curr_j]);
              found_or_edge = true;
            }
            count_path++;
          }
        }
        int adjacent_occupied = std::count(adjacent.begin(), adjacent.end(), '#');
        int adjacent_empty = std::count(adjacent.begin(), adjacent.end(), 'L');
        // Seat empty and no seats
        if ((seat_array[i][j] == 'L') && (adjacent_occupied==0)){
          changed = true;
          new_seat_array[i][j] = '#';
        } else if ((seat_array[i][j] == '#') && (adjacent_occupied >= 5)) {
          // Occupied and shy
          changed = true;
          new_seat_array[i][j] = 'L';
        } else {
          new_seat_array[i][j] = seat_array[i][j];
        }
        // std::cout << adjacent << std::endl;
      }
    }
    //  Apply changes
    for (int i = 0; i < Nrow; i++) {
      for (int j = 0; j < Ncol; j++) {
        seat_array[i][j] = new_seat_array[i][j];
      }
    }
  }

  int count_part2 = 0;
  for (int i = 0; i < Nrow; i++) {
      for (int j = 0; j < Ncol; j++) {
        if (seat_array[i][j] == '#') {
          count_part2++;
        }
      }
    }
  std::cout << count_part2 << std::endl;
}
