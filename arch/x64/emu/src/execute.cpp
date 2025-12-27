#include <xarch/origin/x64/Architecture.hpp>

#include <algorithm>
#include <iostream>

namespace xarch::origin {

void xarch_origin_x64::execute() {
  if (instruction_set.find(this->opcode) != instruction_set.end()) {
    instruction_set[this->opcode](this);
  }
}

} // namespace xarch::origin
