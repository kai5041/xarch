#include <xarch/origin/x64/Architecture.hpp>

#include <cstring>

namespace xarch::origin {

EMU_FFI(setq) {
  auto &entry = arch->get_entry();
  auto &registers = arch->get_registers();

  u8 pos = entry[2];
  if (pos >= registers.size())
    return;

  std::cout << "SETQ\n";
  u64 value = 0;
  std::memcpy(&value, &entry[3], 8);

  registers[pos] = value;
}

} // namespace xarch::origin
