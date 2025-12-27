#pragma once

#include <fstream>
#include <functional>

#include <xarch/origin/x64/instruction_set.hpp>

#include <xwm/Memory.hpp>
#include <xwm/core.hpp>

#include <iostream>

namespace xarch::origin {

class xarch_origin_x64;

using InstructionPtr = std::function<void(xarch_origin_x64 *)>;
using Register = xwm::Memory;

using namespace xwm;

class xarch_origin_x64 : public xwm::Architecture {
protected:
  Map<u16, InstructionPtr> instruction_set;

  u32 exit_status = 0;
  bool interrupt = false;

  Array<u64, 16> registers;
  u64 ip = 0; // Instruction Pointer

  Array<u8, 26> entry;

  u16 opcode = 0;

  Memory oms; // Operational Memory System

public:
  xarch_origin_x64(Dispatcher &dispatcher) : xwm::Architecture(dispatcher) {
    entry.fill(0);
    registers.fill(0);
    init();

    u8 n_args = dispatcher.get_args().size();
    if (n_args) {
      load_file_to_oms(dispatcher.get_args()[0]);
    }
  }

  ~xarch_origin_x64() override {}
  u32 run() override {
    do {
      fetch();
      if (this->interrupt)
        continue;
      decode();
      execute();
    } while (!this->interrupt);

    return this->exit_status;
  }

  void init() {
#define set(n, exec) instruction_set[0x##n] = exec

    set(0001, setq);

    set(FFFF, phlt);

#undef set
  }

  void fetch();
  void decode();
  void execute();

  auto &get_registers() { return registers; }
  auto &get_entry() { return entry; }

  void load_file_to_oms(const std::string &path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file)
      throw std::runtime_error("Failed to open file: " + path);

    std::streamsize file_size = file.tellg();
    if (file_size <= 0)
      throw std::runtime_error("File is empty or unreadable");
    if (file_size % entry.size() != 0)
      throw std::runtime_error(
          "File size is not a multiple of entry size, got: " +
          std::to_string(file_size) + " instead of " +
          std::to_string(entry.size()));

    file.seekg(0, std::ios::beg);

    u64 index = 0;
    u8 byte;
    while (file.read(reinterpret_cast<char *>(&byte), 1)) {
      oms.write(index++, byte);
    }

    if (!file.eof())
      throw std::runtime_error("Error while reading file");
  }
};

} // namespace xarch::origin
