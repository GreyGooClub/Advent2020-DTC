#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
#include <functional>

using namespace std;

const int U = 0;
const int R = 1;
const int D = 2;
const int L = 3;

// const maps are weird...
map<int, int> ADJACENT = {
    {U, D},
    {R, L},
    {D, U},
    {L, R},
};

map<int, pair<int, int>> DIRECTIONS = {
    {U, {1, 0}},
    {R, {0, 1}},
    {D, {-1, 0}},
    {L, {0, -1}},
};

typedef pair<int, int> tile_id; // Name, orientation[0..7]
typedef vector<string> tile_image;
typedef array<int, 4> tile_edges;

struct tile {
  tile_id id;
  tile_edges edges;
  tile_image image;
  set<int> unique_neighbours;
  map<int, set<tile_id>> neighbours; // Potential neighbours
};

tile_image rotate(int n, tile_image data){
  int N = data.size();
  tile_image out;
  for (int i = 0; i < n; i++) {
    tile_image current(N, "");
    for (int j=0; j < N; j++){
      for (int k = 0; k < N; k++){
        current[k] = data[j][k] + current[k];
      }
    }
    data = current;
    out = current;
  }
  return out;
}

tile_image flip_lr(tile_image data) {
  int N = data.size();
  tile_image out;
  for (int i=0; i<N; i++){
    string rev_row = "";
    for (int j=0; j<N; j++){
      rev_row = data[i][j] + rev_row;
    }
    out.push_back(rev_row);
  }
  return out;
}

tile_image flip_ud(tile_image data){
  int N = data.size();
  tile_image out;
  for (int i=N-1; i>=0; i--){
    out.push_back(data[i]);
  }
  return out;
}

map<int, function<tile_image(tile_image)>> TRANSFORMS = {
  // All the 8 unique transformations.
    {0, [](tile_image data) -> tile_image { return data; }},
    {1, [](tile_image data) -> tile_image { return rotate(1, data); }},
    {2, [](tile_image data) -> tile_image { return rotate(2, data); }},
    {3, [](tile_image data) -> tile_image { return rotate(3, data); }},
    {4, [](tile_image data) -> tile_image { return flip_lr(data); }},
    {5, [](tile_image data) -> tile_image { return flip_ud(data); }},
    {6, [](tile_image data) -> tile_image { return flip_lr(rotate(1, data)); }},
    {7, [](tile_image data) -> tile_image { return flip_ud(rotate(1, data)); }},
};

int row_to_int(string row){
  int N = row.size();
  int out = 0;
  for (int i=0; i<N; i++){
    if (row[i]=='#'){
      out += pow(2, i);
    }
  }
  return out;
}

tile_edges tile_edge_codes(tile_image data){
  int N = data.size();
  string top = data[0];
  string right = "";
  string bottom = "";
  string left = "";
  for (int i = 0; i < N; i++) {
    right += data[i][9];
    bottom += data[9][i];
    left += data[i][0];
  }
  vector<string> edge_str = {top, right, bottom, left};
  tile_edges edges;
  for (int i=0; i<4; i++){
    edges[i] = row_to_int(edge_str[i]);
  }
  return edges;
}

tile_image trimmed_tile(tile_image data){
  int N = data.size();
  tile_image out;
  for (int i=1; i<N-1; i++){
    out.push_back(data[i].substr(1, data.size()-2));
  }
  return out;
}

vector<tile> generate_permutations(int tile_name, tile_image data){
  vector<tile> out;
  for (auto [orient, transform] : TRANSFORMS){
    tile new_tile;
    new_tile.id = {tile_name, orient};
    tile_image transformed = transform(data);
    new_tile.edges = tile_edge_codes(transformed);
    new_tile.image = trimmed_tile(transformed);
    out.push_back(new_tile);
  }
  return out;
}

pair<set<int>, set<int>> corners_and_edges(map<tile_id, tile> &tiles) {
  set<int> corners;
  set<int> edges;
  for (auto const &[tid, tile] : tiles) {
    if (tile.unique_neighbours.size() == 2) {
      corners.emplace(tid.first);
    } else if (tile.unique_neighbours.size() == 3) {
      edges.emplace(tid.first);
    }
  }
  return {corners, edges};
}

map<tile_id, tile> fix_tile(tile_id tid, map<tile_id, tile>& tiles) {
  // Fix orientation, remove other options in maps
  map<tile_id, tile> new_map = tiles;
  for (auto [check_tid, check_tile] : tiles) {
    if (check_tid.first == tid.first){
      new_map.erase(check_tid);
    } else {
      new_map[check_tid].unique_neighbours.erase(tid.first);
      for (int i=0; i<4; i++){
        for (int j=0; j<12; j++) {
          new_map[check_tid].neighbours[i].erase(make_pair(tid.first, j));
        }
      }
    }
  }
  return new_map;
}

bool locate_seamonster(int offy, int offx, tile_image sea_monster,
                       tile_image &current) {
  int Nsm_y = sea_monster.size();
  int Nsm_x = sea_monster[0].size();
  bool all_match = true;
  for (int i=0; i<Nsm_y; i++){
    for (int j=0; j<Nsm_x; j++) {
      if (sea_monster[i][j] != '#') {
        continue;
      } else{
        all_match &= (current[i+offy][j+offx] == '#');
      }
    }
  }
  if (all_match){
    for (int i = 0; i < Nsm_y; i++) {
      for (int j = 0; j < Nsm_x; j++) {
        if (sea_monster[i][j] == '#'){
          current[i + offy][j + offx] = 'O';
        }
      }
    }
  }
  return all_match;
}

int main() {

  map<int, map<int, set<tile_id>>> edge_code_map;
  map<tile_id, tile> tiles;

  for (string line; getline(cin, line);){
    int colon = line.find(":");
    int tile_name = stoi(line.substr(5, colon-5));
    getline(cin, line);
    tile_image tile_str;
    while(line.size() > 0){
      tile_str.push_back(line);
      getline(cin, line);
    }

    auto new_tiles = generate_permutations(tile_name, tile_str);
    for (tile curr_tile : new_tiles){
      array<int, 4> edge_set = curr_tile.edges;
      for (unsigned j=0; j<4; j++){
        edge_code_map[edge_set[j]][j].emplace(curr_tile.id);
      }
      tiles[curr_tile.id] = curr_tile;
    }
  }

  for (auto& [tid, curr_tile] : tiles){
    // Iterate over edges
    set<int> uniq_neighb;
    for (int i=0; i<4; i++){
      for (auto [nedge, ntids]: edge_code_map[curr_tile.edges[i]]){
        if (ADJACENT[i]==nedge){
          for (auto ntid : ntids){
            if (ntid.first!=tid.first){
              curr_tile.neighbours[i].emplace(ntid);
              uniq_neighb.emplace(ntid.first);
            }
          }
        }
      }
    }
    curr_tile.unique_neighbours = uniq_neighb;
  }

  auto full_tiles = tiles;
  auto const& [corners, edges] = corners_and_edges(tiles);

  long result = 1;
  for (auto corn : corners){
    result *= corn;
  }
  cout << "Part 1: " << result << endl;

  map<pair<int, int>, tile_id> puzzle;

  tile_id current;
  puzzle = {};
  pair<int, int> location = {0, 0};
  current = {*corners.begin(), 0}; // Select start place
  vector<int> corner_dirs;
  vector<int> directions;
  for (auto [dir, ne] : tiles[current].neighbours){
    corner_dirs.push_back(dir);
    directions.push_back(dir);
  }
  for (auto dir : corner_dirs){
    directions.push_back((dir+2) % 4);
  }
  vector<int> inside_directions;
  for (int i=0; i < 4; i++) {
    int ind = i+1;
    if(ind >= 4){
      ind -= 4;
    }
    inside_directions.push_back(directions[ind]);
  }

  int dir_ind = 0;
  int min_x = 0;
  int min_y = 0;
  int direc = directions[dir_ind];
  int inside_dir = inside_directions[dir_ind];
  while (true) {
    puzzle[location] = current;
    auto curr_ne = tiles[current].neighbours;
    tiles = fix_tile(current, tiles);
    if (curr_ne[direc].size() == 0){
      dir_ind++;
      dir_ind %= 4;
      direc = directions[dir_ind];
      inside_dir = inside_directions[dir_ind];
    }
    auto nexts = curr_ne[direc];
    if (nexts.size() == 0){
      break;
    }
    if (nexts.size()==1){
      // Only choice, continues
      current = *nexts.begin();
    } else {
      // Many choices, choose one with inside neighbours
      for (auto pot_next : nexts){
        auto ne = tiles[pot_next].neighbours;
        if (ne[inside_dir].size() > 0){
          current = pot_next;
          break;
        }
      }
    }
    location.first += DIRECTIONS[direc].first;
    if (location.first < min_y){
      min_y = location.first;
    }
    location.second += DIRECTIONS[direc].second;
    if (location.second < min_x) {
      min_x = location.second;
    }
  }

  int N = sqrt(puzzle.size());
  int Nsub = 8;
  tile_image reconstructed;
  for (int i=N-1; i>=0; i--){   // Start at top row
    // rows
    tile_image current_big_row(Nsub, "");
    for (int j=0; j<N; j++){
      // columns
      tile_id tid = puzzle[{i + min_y, j + min_x}];
      tile_image local_tile = full_tiles[tid].image;
      for (int k=0; k<Nsub; k++){
        current_big_row[k] += local_tile[k];
      }
    }
    for (auto br: current_big_row){
      reconstructed.push_back(br);
    }
  }

  cout << "Reconstructed image: " << endl;
  for (auto row:reconstructed){
    cout << row << endl;
  }
  cout << "------------" << endl;

  tile_image sea_monster = {
      {"                  # "},
      {"#    ##    ##    ###"},
      {" #  #  #  #  #  #   "},
  };
  int Nsm_y = sea_monster.size();
  int Nsm_x = sea_monster[0].size();

  // Slide sea monster across image for all permutations
  // and check matches
  int Nrecon = reconstructed.size();

  for(auto [orient, transform] : TRANSFORMS){
    tile_image current = transform(reconstructed);

    bool located = false;
    for (int offy=0; offy < (Nrecon - Nsm_y); offy++){
      for (int offx=0; offx < (Nrecon - Nsm_x); offx++) {
        located |= locate_seamonster(offy, offx, sea_monster, current);
      }
    }
    if (located){
      reconstructed = current;
      cout << "SEA MONSTERS!!!" << " (Orientation: " << orient << ")" << endl;
      for (auto row : reconstructed) {
        cout << row << endl;
      }
      break;
    }
  }

  int sea_roughness = 0;
  for (auto row : reconstructed) {
    for (auto c: row){
      if (c=='#'){
        sea_roughness++;
      }
    }
  }

  cout << "Sea roughness (Part 2): " << sea_roughness << endl;

}
