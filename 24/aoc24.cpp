#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <valarray>
#include <boost/algorithm/string.hpp>

using namespace std;

map<string, valarray<int>> DIRECTIONS = {
    // x, y, z
    // Hex cubic labeling
    {"e", {1, -1, 0}},
    {"w", {-1, 1, 0}},
    {"se", {1, 0, -1}},
    {"ne", {0, -1, 1}},
    {"sw", {0, 1, -1}},
    {"nw", {-1, 0, 1}},
};

string hash_loc(valarray<int> loc){
  return (to_string(loc[0]) + ","+
          to_string(loc[1]) + ","+
          to_string(loc[2]));
}

valarray<int> unhash_loc(string hloc) {
  vector<string> split_str;
  boost::split(split_str, hloc, boost::is_any_of(","));
  valarray<int> out = {
      stoi(split_str[0]),
      stoi(split_str[1]),
      stoi(split_str[2]),
  };
  return out;
}

int count_black(map<string, int> tile_flips){
  int num_black = 0;
  for (auto [sloc, flips] : tile_flips) {
    num_black += flips % 2;
  }
  return num_black;
}

int main() {

  map<string, int> tile_flips; // 1 if black

  for (string line; getline(cin, line);){
    // cout << line << endl;
    vector<string> directions;
    int curr_loc=0;
    while (curr_loc < line.size()){
      if ((line[curr_loc] == 'n') ||
          (line[curr_loc] == 's')) {
        directions.push_back(line.substr(curr_loc, 2));
        curr_loc += 2;
      } else{
        directions.push_back(line.substr(curr_loc, 1));
        curr_loc += 1;
      }
    }
    valarray<int> loc = {0,0,0}; // Reference tile
    for (string dir : directions){
      loc += DIRECTIONS[dir];
    }
    tile_flips[hash_loc(loc)] += 1;
  }

  cout << "Part 1: " << count_black(tile_flips) << endl;
  cout << endl;

  // Part 2
  int num_days = 100;
  for (int i=1; i<=num_days; i++){
    auto start_flips = tile_flips;
    // Map of white tiles to num black adjacent
    // Only gets evaluated for tiles with atleast 1 black neighbour
    map<string,int> blackn_count;
    // Look over all known tiles;
    for (auto [hloc, flips] : start_flips){
      bool black = flips % 2;
      valarray<int> loc = unhash_loc(hloc);
      if (black){
        // If a black tile, count adjacent black tiles
        int blackn = 0;
        for (auto [dir, mdir] : DIRECTIONS){
          string nhash = hash_loc(loc + mdir);
          bool is_blackn = (start_flips[nhash] % 2);
          blackn += is_blackn;
          // If neighbour is white, increment
          // the number of black adjacents that
          // that white tile has.
          if (not is_blackn){
            blackn_count[nhash] += 1;
          }
        }
        // Flip if matches rule for black tile
        if ((blackn == 0) || (blackn > 2)){
          tile_flips[hloc]++;
        }
      }
    }

    // Find white tiles with 2 black adjacent.
    for (auto [hloc, nblackn] : blackn_count){
      if (nblackn == 2){
        tile_flips[hloc]++;
      }
    }
    cout << "Day " << i << ": " << count_black(tile_flips) << endl;
  }
  cout << endl;
  cout << "Part 2: " << count_black(tile_flips) << endl;
}
