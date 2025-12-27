#include <xarch/origin/x64/Architecture.hpp>

#include <iostream>

namespace xarch::origin {

void xarch_origin_x64::decode() {
  opcode = (u16(this->entry[0]) << 8 | u8(this->entry[1])) & 0xFFFF;
}

} // namespace xarch::origin
