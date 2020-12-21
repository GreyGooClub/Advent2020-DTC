#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <boost/algorithm/string.hpp>

using namespace std;

int main() {

  map<string, set<string>> allergen_map;
  set<string> no_allergen_ing;
  set<string> all_allergens;
  vector<set<string>> all_foods;

  for (string line; getline(cin, line);){
    int start_paren = line.find('(');
    string ig_str = line.substr(0, start_paren);
    int start_allergens = start_paren + 9;
    string al_str = line.substr(start_allergens, line.size()-1-start_allergens);
    boost::trim(al_str);
    boost::trim(ig_str);
    vector<string> ingredients;
    boost::split(ingredients, ig_str, boost::is_any_of(" "));
    vector<string> allergens;
    boost::split(allergens, al_str, boost::is_any_of(","));
    set<string> ig_set;
    for (string ig : ingredients){
      boost::trim(ig);
      no_allergen_ing.emplace(ig);
      ig_set.emplace(ig);
    }
    all_foods.push_back(ig_set);
    for (string al : allergens) {
      boost::trim(al);
      all_allergens.emplace(al);
      if (allergen_map.find(al) == allergen_map.end()) {
        allergen_map[al] = ig_set;
      } else {
        set<string> intersection;
        set<string> existing_set = allergen_map[al];
        set_intersection(ig_set.begin(), ig_set.end(),
                         existing_set.begin(), existing_set.end(),
                         inserter(intersection, intersection.begin()));
        allergen_map[al] = intersection;
      }
    }
  }

  // Collect results
  map<string, string> allergen_result;
  bool not_done = true;
  while (not_done){
    for (auto al : all_allergens){
      if (allergen_map[al].size()==1){
        string ing = *(allergen_map[al].begin());
        allergen_result[al] = ing;
        no_allergen_ing.erase(ing);
        allergen_map.erase(al);
        for (auto al : all_allergens) {
          allergen_map[al].erase(ing);
        }
      }
    }
    if (allergen_result.size() == all_allergens.size()){
      not_done = false;
    }
  }

  int num_appearances = 0;
  for (auto ing_set: all_foods){
    for (auto ing : no_allergen_ing){
      if (ing_set.find(ing) != ing_set.end()){
        num_appearances++;
      }
    }
  }
  cout << "Part 1: " << num_appearances << endl;

  // I used an ordered map so...
  cout << "Part 2: |";
  unsigned count = 0;
  for (auto [al, ing] : allergen_result){
    cout << ing;
    if (count != allergen_result.size()-1){
      cout << ",";
    }
    count++;
 }
  cout << "|" << endl;
}
