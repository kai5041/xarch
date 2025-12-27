#include <xarch/origin/x64/Architecture.hpp>

#include <iostream>

namespace xarch::origin {

void xarch_origin_x64::fetch() {
  if (ip >= oms.get_memory().size()) {
    this->interrupt = true;
    return;
  }

  for (u8 i = 0; i < entry.size(); i++) {
    entry[i] = oms.read(ip++);
  }

  std::cout << "[fetch] ip=" << ip - entry.size()
            << ", entry[0]=" << (int)entry[0] << std::endl;
}

} // namespace xarch::origin