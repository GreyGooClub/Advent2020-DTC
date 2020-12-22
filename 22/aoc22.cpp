#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>

using namespace std;

typedef vector<int> deck;
typedef string deck_hash;

deck play_part1(deck p1_deck, deck p2_deck){
  while ((p1_deck.size() > 0) && (p2_deck.size() > 0)) {
    int p1_top = p1_deck[0];
    p1_deck.erase(p1_deck.begin());
    int p2_top = p2_deck[0];
    p2_deck.erase(p2_deck.begin());
    if (p1_top > p2_top) {
      p1_deck.push_back(p1_top);
      p1_deck.push_back(p2_top);
    } else {
      p2_deck.push_back(p2_top);
      p2_deck.push_back(p1_top);
    }
  }

  deck winning_deck;
  if (p1_deck.size() != 0) {
    winning_deck = p1_deck;
  } else {
    winning_deck = p2_deck;
  }
  return winning_deck;
}

long score(deck deck_to_score){
  long result = 0;
  int N = deck_to_score.size();
  for (int i = 0; i < N; i++) {
    result += deck_to_score[i] * (N - i);
  }
  return result;
}

deck_hash hash_deck(deck deck_to_hash) {
  // Super fancy hash function to show off to
  // your number theory friends.
  return to_string(score(deck_to_hash));
}

typedef pair<bool, deck> game_result; // first=true -> P1 win.

game_result play_part2(deck p1_deck, deck p2_deck) {

  set<deck_hash> hashes = {};
  while ((p1_deck.size() > 0) && (p2_deck.size() > 0)) {
    deck_hash hash = hash_deck(p1_deck)+","+hash_deck(p2_deck);
    bool in_hash = hashes.count(hash);
    if (in_hash) {
      // P1 wins
      return {true, p1_deck};
    }
    hashes.emplace(hash);

    // Draw cards
    int p1_card = p1_deck[0];
    p1_deck.erase(p1_deck.begin());
    int p2_card = p2_deck[0];
    p2_deck.erase(p2_deck.begin());

    // Do we recurse?
    bool p1_win;
    if (((int)p1_deck.size() >= p1_card) &&
        ((int)p2_deck.size() >= p2_card)) {
      // Yes
      deck sg_p1_deck(p1_deck.begin(), p1_deck.begin() + p1_card);
      deck sg_p2_deck(p2_deck.begin(), p2_deck.begin() + p2_card);

      game_result sg_result = play_part2(sg_p1_deck, sg_p2_deck);
      p1_win = sg_result.first;
    } else{
      p1_win = (p1_card > p2_card);
    }

    if (p1_win){
      p1_deck.push_back(p1_card);
      p1_deck.push_back(p2_card);
    } else {
      p2_deck.push_back(p2_card);
      p2_deck.push_back(p1_card);
    }
  }

  if (p1_deck.size() != 0) {
    return {true, p1_deck};
  } else {
    return {false, p2_deck};
  }
}

int main() {

  deck p1_deck_input;
  deck p2_deck_input;

  deck *curr_deck = &p1_deck_input;

  // Read input
  for (string line; getline(cin, line);){
    if (line[0] == 'P'){
      continue;
    } else if (line.size()==0){
      curr_deck = &p2_deck_input;
    } else{
      (*curr_deck).push_back(stoi(line));
    }
  }

  // Part 1
  deck winning_deck_pt1 = play_part1(p1_deck_input, p2_deck_input);
  long part1_result = score(winning_deck_pt1);
  cout << "Part 1: " << part1_result << endl;

  // Part 2
  deck winning_deck_pt2 = play_part2(p1_deck_input, p2_deck_input).second;
  long part2_result = score(winning_deck_pt2);
  cout << "Part 2: " << part2_result << endl;
}
