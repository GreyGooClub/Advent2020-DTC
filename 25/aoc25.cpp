#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

const long MODULO = 20201227;

long transform(long sub_num, long start_value, long Niter){
  long value = start_value;
  for (long i=0; i<Niter; i++){
    value = (value*sub_num) % MODULO;
  }
  return value;
}

long find_loop_size(long sub_num, long public_key){
  long loop_size = 1;
  long curr_val = 1;
  while (true){
    curr_val = transform(sub_num, curr_val, 1);
    if (curr_val == public_key){
      return loop_size;
    } else {
      loop_size++;
    }
  }
}

using namespace std;

int main() {

  string card_pub_str;
  getline(cin, card_pub_str);
  long card_pub = stoi(card_pub_str);
  string door_pub_str;
  getline(cin, door_pub_str);
  long door_pub = stoi(door_pub_str);

  cout << card_pub << endl;
  cout << door_pub << endl;

  long card_loop_size = find_loop_size(7, card_pub);
  cout << "Card loop size: " << card_loop_size << endl;
  long door_loop_size = find_loop_size(7, door_pub);
  cout << "Door loop size: " << door_loop_size << endl;

  cout << "Encryption key (from card): "
       << transform(door_pub, 1, card_loop_size) << endl;
  cout << "Encryption key (from door): "
       << transform(card_pub, 1, door_loop_size) << endl;
}
