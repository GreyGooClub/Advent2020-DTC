#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>

int evaluate_command(std::string cmd, int value, int* accumulator){
  // Returns command index increment
  if (cmd == "nop") {
    return 1;
  } else if (cmd == "acc") {
    *accumulator += value;
    return 1;
  } else if (cmd == "jmp") {
    return value;
  }
  return 0;                     //  Shouldn't happen
}

int accumulate(std::vector<std::string> cmds,
               std::vector<int> values){
  int accumulator = 0;
  int cmd_index = 0;
  std::vector<int> instructions_run = {};

  while (std::count(instructions_run.begin(), instructions_run.end(),
                    cmd_index) < 1) {
    instructions_run.push_back(cmd_index);
    cmd_index += evaluate_command(cmds[cmd_index],
                                  values[cmd_index],
                                  &accumulator);
  }
  return accumulator;
}

int accumulate_with_swap(std::vector<std::string> cmds,
                         std::vector<int> values, int swap_index) {

  int cmd_index = 0;
  std::vector<int> instructions_run = {};
  int total_cmds = cmds.size();
  int accumulator = 0;

  while (std::count(instructions_run.begin(), instructions_run.end(),
                    cmd_index) < 1) {

    if (cmd_index >= total_cmds) {
      return accumulator;
      std::cout << "Successfully ran to end!" << std::endl;
      break;
    }

    instructions_run.push_back(cmd_index);
    std::string cmd = cmds[cmd_index];

    if (cmd_index == swap_index) {
      if (cmd == "nop") {
        cmd = "jmp";
      } else if (cmd == "jmp") {
        cmd = "nop";
      }
    }
    cmd_index += evaluate_command(cmd, values[cmd_index], &accumulator);
  }
  return 0;
}

int main() {

  std::vector<std::string> cmds;
  std::vector<int> values;

  for (std::string line; std::getline(std::cin, line);){
    std::string cmd = line.substr(0, line.find(' '));
    int value = std::stoi(line.substr(line.find(' ')+1, std::string::npos));
    cmds.push_back(cmd);
    values.push_back(value);
  }

  std::cout << "Final accumulator value (Part 1): "
            << accumulate(cmds, values) << std::endl;

  // Part 2
  int i = cmds.size()-1;
  int accumulator_pt2 = 0;

  //  Just brute force changes. Starting at end maybe helps?
  while (accumulator_pt2 == 0){
    if ((cmds[i] == "jmp") || (cmds[i] == "nop")) {
      accumulator_pt2 = accumulate_with_swap(cmds, values, i);
    }
    i--;
  }
  std::cout << "Final accumulator value (Part 2): " << accumulator_pt2 << std::endl;
}
