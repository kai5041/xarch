#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <regex>

#include <iostream>

std::vector<std::string> tokenize_line(std::string line) {
  std::vector<std::string> tokens;

  std::stringstream ss(line);
  std::string token;
  while (ss >> token) {
    tokens.push_back(token);
  }

  return tokens;
}

struct Instruction {
  std::uint16_t opcode;
  std::vector<std::string> parameters;
};

std::unordered_map<std::string, Instruction> instructions;

void add_instruction(const std::string& name, const Instruction instruction) {
  instructions[name] = instruction;
}

void compile_file(std::string file_path) {
  std::fstream file(file_path, std::ios::in);

  std::uint32_t y = 1;

  std::vector<std::uint8_t> out;

  std::string line;
  while (std::getline(file, line)) {
    line.erase(line.begin(),
      std::find_if(line.begin(), line.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
    if (line.empty() || line[0] == '#') {
      continue;
    }

    std::vector<std::string> tokens = tokenize_line(line);
    const auto& operation = tokens[0];
    auto it = instructions.find(operation);
    if (it == instructions.end()) {
      std::cout << "[ERROR] xasmc: Mnemonic '" << operation << "' not found (line " << std::to_string(y) << ")" << std::endl;
      exit(1);
    }

    if (it->second.parameters.size() != tokens.size() - 1) {
      std::cout << "[ERROR] xasmc: Not enough params for '" << operation << "' (line " << std::to_string(y) << ")" << std::endl;
      exit(1);
    }

    auto& opcode = it->second.opcode;
    uint8_t upper = static_cast<uint8_t>((opcode >> 8) & 0xFF);
    uint8_t lower = static_cast<uint8_t>(opcode & 0xFF);

    out.push_back(lower);
    out.push_back(upper);

    if (it->second.parameters.size() == 0)
      continue;


    for (std::size_t i = 0; i < it->second.parameters.size(); i++) {
      auto& param = it->second.parameters[i];

      if (param[0] == 'r') {
        std::regex r(R"(R(\d+)([BWLQ])(\d+))");
        std::smatch m;
        std::string& s = tokens[i];

        if (std::regex_match(s, m, r)) {
          int  x = std::stoi(m[1].str());  // register index
          char B = m[2].str()[0];          // type
          int  y = std::stoi(m[3].str());  // offset

          std::cout << x << " : " << B << " : " << y << std::endl;
        }
        
        if (param == "r8") {

        }
        else {
          std::cout << "Unsupported bit width" << std::endl;;
        }
      }


    }

    y++;
  }
}

int main() {
  add_instruction("setb", { 0x1, {"r8", ""} });
  add_instruction("setw", { 0x2, {"r8", ""} });
  add_instruction("print", { 0xFFFF, {} });

  compile_file("test.xasm");

  return 0;
}
