#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>


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

std::string find_immediate_neighbours(int i, int j,
                                      const std::vector<std::string>& seats) {
  const int Nrow = seats.size();
  const int Ncol = seats[0].size();
  std::string adjacent;
  for (int k = 0; k < 8; k++) {
    int curr_i = i + adjacency_row[k];
    int curr_j = j + adjacency_col[k];
    if ((curr_i < 0) || (curr_j < 0) || (curr_i >= Nrow) || (curr_j >= Ncol)) {
      continue;
    } else {
      adjacent.push_back(seats[curr_i][curr_j]);
    }
  }
  return adjacent;
}

std::string find_directional_neighbours(int i, int j,
                                        const std::vector<std::string> &seats) {
  const int Nrow = seats.size();
  const int Ncol = seats[0].size();
  std::string adjacent;

  for (int k = 0; k < 8; k++) {
    int count_path = 1;
    bool found_or_edge = false;
    while (not found_or_edge) {
      int curr_i = i + adjacency_row[k] * count_path;
      int curr_j = j + adjacency_col[k] * count_path;
      if ((curr_i < 0) || (curr_j < 0) || (curr_i >= Nrow) ||
          (curr_j >= Ncol)) {
        found_or_edge = true;
      } else if (seats[curr_i][curr_j] != '.') {
        adjacent.push_back(seats[curr_i][curr_j]);
        found_or_edge = true;
      }
      count_path++;
    }
  }
  return adjacent;
}

int main() {

  std::vector<std::string> start_seats;

  for (std::string line; std::getline(std::cin, line);){
    start_seats.push_back(line);
  }

  const int Nrow = start_seats.size();
  const int Ncol = start_seats[0].size();

  // Part 1
  bool changed = true;
  std::vector<std::string> seats = start_seats;
  std::vector<std::string> new_seats = seats;

  while (changed) {
    changed = false;
    for (int i=0; i < Nrow; i++){
      for (int j=0; j < Ncol; j++){
        std::string adjacent = find_immediate_neighbours(i, j, seats);
        int adjacent_occupied = std::count(adjacent.begin(), adjacent.end(), '#');
        // Seat empty and no seats
        if ((seats[i][j] == 'L') && (adjacent_occupied==0)){
          changed = true;
          new_seats[i][j] = '#';
        } else if ((seats[i][j] == '#') && (adjacent_occupied >= 4)) {
          // Occupied and shy
          changed = true;
          new_seats[i][j] = 'L';
        } else {
          new_seats[i][j] = seats[i][j];
        }
      }
    }
    //  Apply changes
    seats = new_seats;
  }

  int count_part1 = 0;
  for (auto row : seats) {
    count_part1 += std::count(row.begin(), row.end(), '#');
  }
  std::cout << "Part 1: " << count_part1 << std::endl;

  // Part 2
  changed = true;
  seats = start_seats;
  new_seats = seats;

  while (changed) {
    changed = false;
    for (int i = 0; i < Nrow; i++) {
      for (int j = 0; j < Ncol; j++) {
        std::string adjacent = find_directional_neighbours(i, j, seats);
        int adjacent_occupied =
            std::count(adjacent.begin(), adjacent.end(), '#');
        // Seat empty and no seats
        if ((seats[i][j] == 'L') && (adjacent_occupied == 0)) {
          changed = true;
          new_seats[i][j] = '#';
        } else if ((seats[i][j] == '#') && (adjacent_occupied >= 5)) {
          // Occupied and shy
          changed = true;
          new_seats[i][j] = 'L';
        } else {
          new_seats[i][j] = seats[i][j];
        }
      }
    }
    //  Apply changes
    seats = new_seats;
  }

  int count_part2 = 0;
  for (auto row : seats) {
    count_part2 += std::count(row.begin(), row.end(), '#');
  }
  std::cout << "Part 2: " << count_part2 << std::endl;
}
