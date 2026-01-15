#include <xarch/origin/x64/instruction_set.hpp>

#include <xarch/origin/x64/Architecture.hpp>

#include <iomanip>
#include <iostream>

namespace xarch::origin {

/*
EMU_FFI(phlt) {
  auto &regs = arch->get_registers();

  for (u8 i = 0; i < regs.size(); i++) {
    const int width = sizeof(regs[i]) * 2;

    std::cout << "R" << std::dec << static_cast<int>(i) << " = " << std::hex
              << std::uppercase << std::setw(width) << std::setfill('0')
              << regs[i] << std::dec << "\t";

    if ((i + 1) % 2 == 0) {
      std::cout << std::endl;
    }
  }

  if (regs.size() % 2 != 0) {
    std::cout << std::endl;
  }
}
*/

} // namespace xarch::origin
