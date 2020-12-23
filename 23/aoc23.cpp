#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Cup {
  int value;
  int next;
};

typedef unordered_map<int, Cup> Cups;

int play_move(int current_cup, Cups& cups) {

  Cups pickup;
  Cup pu_cup = cups[current_cup];
  int pickup_start = cups[current_cup].next;
  int last_pickup;
  for (int i = 0; i < 3; i++) {
    pu_cup = cups[pu_cup.next];
    pickup[pu_cup.value] = pu_cup;
    cups[current_cup].next = pu_cup.next;
    last_pickup = pu_cup.value;
  }

  int max = cups.size();
  int min = 1;
  while (pickup.find(max) != pickup.end()){
    max--;
  }
  while (pickup.find(min) != pickup.end()) {
    min++;
  }

  int dest_cup;
  if (current_cup == 1){
    dest_cup = max;
  } else{
    dest_cup = current_cup - 1;
    while (pickup.find(dest_cup) != pickup.end()) {
      dest_cup--;
      if (dest_cup < min) {
        dest_cup = max;
        break;
      }
    }
  }

  int pickup_end = cups[dest_cup].next;
  cups[dest_cup].next = pickup_start;
  cups[last_pickup].next = pickup_end;

  return cups[current_cup].next;
}

int main() {

  string line;
  getline(cin, line);

  vector<int> start_cups;
  for (char c : line){
    start_cups.push_back(stoi(to_string(c))-48);
  }

  int num_cups = start_cups.size();

  Cups cup_map;
  for (int i=0; i<num_cups;i++){
    Cup cup;
    cup.value = start_cups[i];
    cup.next = start_cups[(i+1) % num_cups];
    cup_map[start_cups[i]] = cup;
  }

  int moves = 100;
  int current_cup = start_cups[0];
  for (int i = 1; i <= moves; i++) {
    // cout << "Move " << i << endl;
    current_cup = play_move(current_cup, cup_map);
  }

  Cup next_cup = cup_map[cup_map[1].next];
  cout << "Part 1: ";
  for (int i=0; i<num_cups-1;i++){
    cout << next_cup.value;
    next_cup = cup_map[next_cup.next];
  }
  cout << endl;

  // Part 2
  Cups cup_map_pt2;
  int extended_cups = 1000000;
  for (int i = 0; i < extended_cups; i++) {
    Cup cup;
    if (i < num_cups){
      cup.value = start_cups[i];
      if (i < num_cups-1){
        cup.next = start_cups[(i+1)];
      } else {
        cup.next = i+2;
      }
      cup_map_pt2[cup.value] = cup;
    } else{
      cup.value = i+1;
      if (i < extended_cups-1){
        cup.next = i+2;
      } else {
        cup.next = start_cups[0];
      }
      cup_map_pt2[cup.value] = cup;
    }
  }

  moves = 10000000;
  current_cup = start_cups[0];
  for (int i = 1; i <= moves; i++) {
    current_cup = play_move(current_cup, cup_map_pt2);
  }

  cout << cup_map_pt2[1].next <<  endl;
  cout << cup_map_pt2[cup_map_pt2[1].next].next << endl;

  long long result = ((long long)cup_map_pt2[1].next *
                      (long long)cup_map_pt2[cup_map_pt2[1].next].next);
  cout << "Part 2: " << result << endl;
}
