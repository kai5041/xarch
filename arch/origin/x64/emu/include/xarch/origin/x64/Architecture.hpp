#pragma once

#include <fstream>
#include <functional>

#include <xarch/origin/x64/instruction_set.hpp>

#include <xwm/Memory.hpp>
#include <xwm/core.hpp>

#include <iostream>

namespace xarch::origin {

  class xarch_origin_x64;

  using InstructionPtr = std::function<void(xarch_origin_x64*)>;
  using Register = xwm::Memory;

  using namespace xwm;

  class xarch_origin_x64 : public xwm::Architecture {
  protected:
    Map<u16, InstructionPtr> instruction_set;

  public:
    xarch_origin_x64(Dispatcher& dispatcher) : xwm::Architecture(dispatcher) {
    }

    ~xarch_origin_x64() override {}
    u32 run() override {
      std::cout << "run" << std::endl;
      return 0;
    }

    void init() {
#define set(n, exec) instruction_set[0x##n] = exec

      //set(0001, setq);
      //set(FFFF, phlt);

#undef set
    }

  };

} // namespace xarch::origin
