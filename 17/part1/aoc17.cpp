#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <new>

void expand(std::vector<std::vector<std::vector<char>>>& state_vec){
  int Nz = state_vec.size();
  int Ny = state_vec[0].size();

  for (int iz = 0; iz < Nz; iz++) {
    for (int iy = 0; iy < Ny; iy++){
      state_vec[iz][iy].push_back('.');
      state_vec[iz][iy].insert(state_vec[iz][iy].begin(), '.');
    }
  }
  std::vector<char> row_blank;
  row_blank.assign(state_vec[0][0].size(), '.');
  for (int iz = 0; iz < Nz; iz++) {
    state_vec[iz].push_back(row_blank);
    state_vec[iz].insert(state_vec[iz].begin(), row_blank);
  }
  std::vector<std::vector<char>> plane_blank;
  plane_blank.assign(state_vec[0].size(), row_blank);
  state_vec.push_back(plane_blank);
  state_vec.insert(state_vec.begin(), plane_blank);
}

void print_state(std::vector<std::vector<std::vector<char>>>& state_vec) {
  int Nz = state_vec.size();
  int Ny = state_vec[0].size();
  for (int iz = 0; iz < Nz; iz++) {
    std::cout << "iz = " << iz << std::endl;
    for (int iy = 0; iy < Ny; iy++) {
      for (auto c : state_vec[iz][iy]) {
        std::cout << c;
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

int main() {

  // I regret using vectors...
  std::vector<std::vector<std::vector<char>>> state_vec;
  std::vector<std::vector<char>> start_vec;

  for (std::string line; std::getline(std::cin, line);){
    std::vector<char> line_vec;
    for (auto l : line){
      line_vec.push_back(l);
    }
    start_vec.push_back(line_vec);
  }

  state_vec.push_back(start_vec);
  print_state(state_vec);

  // Collect neighbour offsets
  std::vector<std::array<int, 3>> neighbours;
  for (int i = -1; i < 2; i++){
    for (int j = -1; j < 2; j++) {
      for (int k = -1; k < 2; k++) {
        if ((i == 0) & (j == 0) & (k == 0)){
          continue;
        }
        std::array<int, 3> loc = {i, j, k};
        neighbours.push_back(loc);
      }
    }
  }

  expand(state_vec);
  for (int n=0; n<6; n++){
    expand(state_vec);
    auto new_state = state_vec;
    // print_state(new_state);
    int Nz = state_vec.size();
    int Ny = state_vec[0].size();
    int Nx = state_vec[0][0].size();
    std::cout << Nz << " " << Ny << " " << Nz << std::endl;

    for (int iz = 1; iz < Nz-1; iz++) {
      for (int iy = 1; iy < Ny-1; iy++){
        for (int ix = 1; ix < Nx-1; ix++){
          int neigh_count = 0;
          char curr_val = state_vec[iz][iy][ix];
          for (auto ne : neighbours){
            char nval = state_vec[iz+ne[0]][iy+ne[1]][ix+ne[2]];
            if (nval == '#'){
              neigh_count++;
            }
          }
          if (curr_val=='#'){
            if ((neigh_count!=2) && (neigh_count!=3)){
              // std::cout << iz << " " << iy << " " << ix << std::endl;
              new_state[iz][iy][ix] = '.'; // deactivate
            }
          } else if (neigh_count==3){
            new_state[iz][iy][ix] = '#'; // become active
          }
        }
      }
    }
    state_vec = new_state;
    // print_state(state_vec);
  }

  int num_active = 0;
  int Nz = state_vec.size();
  int Ny = state_vec[0].size();
  int Nx = state_vec[0][0].size();
  for (int iz = 1; iz < Nz - 1; iz++) {
    for (int iy = 1; iy < Ny - 1; iy++) {
      for (int ix = 1; ix < Nx - 1; ix++) {
        if (state_vec[iz][iy][ix] == '#'){
          num_active++;
        }
      }
    }
  }
  std::cout << "Number active: " << num_active << std::endl;
}
