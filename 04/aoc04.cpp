#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

std::regex hcl_regex("#[0-9a-f]+");
std::regex pid_regex("^[0-9]{9}$");
std::regex ecl_regex("^(amb|blu|brn|gry|grn|hzl|oth)$");

bool validate_int_range(std::string field, int lower, int upper){
  int field_int = std::stoi(field);
  return ((field_int >= lower) && (field_int <= upper));
}

bool validate_height(std::string field){
  std::size_t found_cm = field.find("cm");
  std::size_t found_in = field.find("in");
  if (found_cm != std::string::npos){
    int height = std::stoi(field.substr(0, found_cm));
    return ((height >= 150) && (height <= 193));
  }
    else if (found_in != std::string::npos) {
    int height = std::stoi(field.substr(0, found_in));
    return ((height >= 59) && (height <= 76));
  } else return false;
}

// Register validators for each field
const std::map<std::string, std::function<bool(std::string)>> requirements_dict = {
  {"ecl", [](std::string field) -> bool {return std::regex_search(field, ecl_regex);}},
  {"pid", [](std::string field) -> bool {return std::regex_search(field, pid_regex);}},
  {"eyr", [](std::string field) -> bool {return validate_int_range(field, 2020, 2030);}},
  {"hcl", [](std::string field) -> bool {return std::regex_search(field, hcl_regex);}},
  {"byr", [](std::string field) -> bool {return validate_int_range(field, 1920, 2002);}},
  {"iyr", [](std::string field) -> bool {return validate_int_range(field, 2010, 2020);}},
  {"hgt", &validate_height},
};

int main() {

  std::vector<std::string> all_lines;
  int num_req = requirements_dict.size();

  for (std::string line; std::getline(std::cin, line);){
    all_lines.push_back(line);
  }

  int num_lines = all_lines.size();
  int num_valid_pt1 = 0;
  int num_valid_pt2 = 0;

  int i = 0;
  while (i < num_lines){
    bool end_of_entry = false;
    std::string current_entry;
    int valid_entries_found_pt1 = 0;
    int valid_entries_found_pt2 = 0;

    //  Gather entry across lines
    while (not end_of_entry){
      std::string curr_line = all_lines[i];
      i++;
      current_entry += curr_line;
      if (curr_line.size() < 1){
          end_of_entry = true;
      } else {
        current_entry += " ";
      }
    }

    std::cout << current_entry << std::endl;

    // iterate over requirements map and validate using registered validators
    for (const auto &element : requirements_dict){
      std::string rfield = element.first;
      std::function<bool(std::string)> validator = element.second;
      std::size_t found_start = current_entry.find(rfield);
      if (found_start != std::string::npos){ // Field exists in entry
        valid_entries_found_pt1++;

        // Locate field value
        std::size_t found_end = current_entry.find_first_of(" ", found_start);
        std::string field_value = current_entry.substr(found_start+4, found_end-found_start-4);

        // Validate against registered validator
        if (validator(field_value)){
            valid_entries_found_pt2++;
            std::cout << rfield << ' ' << field_value << " VALID" <<std::endl;
        } else{
          std::cout << rfield << ' ' << field_value << " INVALID" <<std::endl;
        }
      }
    }
    // All valid for part 1
    if (valid_entries_found_pt1 == num_req){
      num_valid_pt1++;
    }
    // All valid for part 2
    if (valid_entries_found_pt2 == num_req){
      num_valid_pt2++;
    }
  }
  std::cout << "Valid entries found (Part 1): " << num_valid_pt1 << std::endl;
  std::cout << "Valid entries found (Part 2): " << num_valid_pt2 << std::endl;
}
