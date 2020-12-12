#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

std::pair<long, long> rotate_with_ints(int value, long ew, long ns){
  double rot = ((double)value) * M_PI / 180;
  int srot = (int)std::sin(rot);
  int crot = (int)std::cos(rot);
  int n_ew = crot * ew - srot * ns;
  int n_ns = srot * ew + crot * ns;
  return {n_ew, n_ns};
}

int main() {

  std::vector<long> values;
  std::vector<char> cmds;

  for (std::string line; std::getline(std::cin, line);){
    cmds.push_back(line[0]);
    values.push_back(std::stol(line.substr(1, std::string::npos)));
  }

  int Ncmds = cmds.size();

  //  Part 1
  long ew = 0;
  long ns = 0;
  std::vector<char> dir_order = {'N', 'E', 'S', 'W'};
  int facing_direc = 1;

  for (int i=0; i < Ncmds; i++){
    char curr_move_dir = '#';
    long curr_value = values[i];

    if (std::find(dir_order.begin(), dir_order.end(), cmds[i]) != dir_order.end()){
      // Moving a direction
      curr_move_dir = cmds[i];
    } else if (cmds[i] == 'F'){
      curr_move_dir = dir_order[facing_direc];
    } else if (cmds[i] == 'R'){
      facing_direc += curr_value / 90;
      facing_direc = facing_direc % dir_order.size();
      curr_move_dir = dir_order[facing_direc];
      curr_value = 0;
    } else if (cmds[i] == 'L'){
      facing_direc -= curr_value / 90;
      while (facing_direc < 0){
        facing_direc += dir_order.size();
      }
      curr_move_dir = dir_order[facing_direc];
      curr_value = 0;
    }

    if (curr_move_dir == 'E') {
      ew += curr_value;
    } else if (curr_move_dir == 'W') {
      ew -= curr_value;
    } else if (curr_move_dir == 'N') {
      ns += curr_value;
    } else if (curr_move_dir == 'S') {
      ns -= curr_value;
    }
  }

  long dist = std::abs(ew) + std::abs(ns);
  std::cout << "Part 1: " <<  dist << std::endl;

  // part 2
  long ship_ew = 0;
  long ship_ns = 0;
  long wp_ew = 10;
  long wp_ns = 1;

  for (int i=0; i < Ncmds; i++){
    char curr_move_dir = '#';
    long curr_value = values[i];

    if (std::find(dir_order.begin(), dir_order.end(), cmds[i]) != dir_order.end()){
      // Moving a direction
      curr_move_dir = cmds[i];
    } else if (cmds[i] == 'F'){
      ship_ew += wp_ew * curr_value;
      ship_ns += wp_ns * curr_value;
    } else if (cmds[i] == 'R'){
      // Rotate counter clokwise
      auto rotated = rotate_with_ints(-1*curr_value, wp_ew, wp_ns);
      wp_ew = rotated.first;
      wp_ns = rotated.second;
    } else if (cmds[i] == 'L'){
      // Rotate clockwise
      auto rotated = rotate_with_ints(curr_value, wp_ew, wp_ns);
      wp_ew = rotated.first;
      wp_ns = rotated.second;
    }

    if (curr_move_dir == 'E') {
      wp_ew += curr_value;
    } else if (curr_move_dir == 'W') {
      wp_ew -= curr_value;
    } else if (curr_move_dir == 'N') {
      wp_ns += curr_value;
    } else if (curr_move_dir == 'S') {
      wp_ns -= curr_value;
    }
  }

  long dist_pt2 = std::abs(ship_ew) + std::abs(ship_ns);
  std::cout << "Part 1: " << dist_pt2 << std::endl;
}
