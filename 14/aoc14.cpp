#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <cinttypes>

std::uint64_t apply_mask(std::string mask, std::uint64_t value){
  std::uint64_t keep = 0;
  std::uint64_t alter = 0;
  for (int i=0; i < 36; i++){
    if (mask[i] == 'X'){
      keep += std::pow(2, 35-i);
    } else if (mask[i] == '1') {
      alter += std::pow(2, 35 - i);
    }
  }
  return (value & keep) + alter;
}

std::vector<std::uint64_t> fetch_addresses(std::string mask, std::uint64_t addr){
  std::uint64_t keep = 0;
  std::uint64_t alter = 0;
  std::vector<std::uint64_t> float_vals = {0};
  for (int i = 0; i < 36; i++) {
    if (mask[i] == '0') {
      keep += std::pow(2, 35 - i);
    } else if (mask[i] == '1') {
      alter += std::pow(2, 35 - i);
    } else if (mask[i] == 'X'){
      std::vector<std::uint64_t> curr_vals = float_vals; //  Make copy
      for (auto cval : curr_vals){
        float_vals.push_back(cval + std::pow(2, 35 - i));
      }
    }
  }
  std::vector<std::uint64_t> out;
  std::uint64_t nominal = (addr & keep) + alter;
  for (auto val : float_vals) {
    out.push_back(nominal + val);
  }
  return out;
}

int main() {

  std::map<std::uint64_t, std::uint64_t> memory;
  std::map<std::uint64_t, std::uint64_t> memory_pt2;
  std::string curr_mask;

  for (std::string line; std::getline(std::cin, line);) {
    if (line[1] == 'e'){
      // mem
      int loc_val = line.find_last_of(' ');
      std::string val_str = line.substr(loc_val+1, line.size()-loc_val);
      std::uint64_t val = std::stoull(val_str);
      int brac_loc_start = line.find('[');
      int brac_loc_end = line.find(']');
      std::string addr_str = line.substr(brac_loc_start+1, brac_loc_end-brac_loc_start);
      std::uint64_t addr = std::stoull(addr_str);
      std::uint64_t result = apply_mask(curr_mask, val);
      std::cout << "MEM: " << addr << " " << val << " " << result << std::endl;
      memory[addr] = result;
      std::vector<std::uint64_t> addr_part2 = fetch_addresses(curr_mask, addr);
      for (auto addr : addr_part2){
        memory_pt2[addr] = val;
        std::cout << addr << " ";
      }
      std::cout << std::endl;

    } else if (line[1] == 'a'){
      // mask
      int loc = line.find_last_of(' ');
      curr_mask = line.substr(loc + 1, 36);
      std::cout << "MASK: " << curr_mask << std::endl;
    }
  }

  std::uint64_t total_in_mem = 0;
  for (auto const &[maddr, mval] : memory) {
    total_in_mem += mval;
  }
  std::cout << "Part 1: " << total_in_mem << std::endl;

  std::uint64_t total_in_mem_pt2 = 0;
  for (auto const &[maddr, mval] : memory_pt2) {
    total_in_mem_pt2 += mval;
  }
  std::cout << "Part 2: " << total_in_mem_pt2 << std::endl;
}
