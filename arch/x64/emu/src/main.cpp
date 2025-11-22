#include <iostream>

#include <xwm/architecture.hpp>
#include <xwm/cli.hpp>

extern "C" {

class MyArchitecture : public xwm::Architecture {
public:
  MyArchitecture(xwm::Vec<std::string> args) : Architecture(std::move(args)) {}
  ~MyArchitecture() override = default;

  int run() noexcept override {
    std::cout << "Hello World!" << std::endl;
    return 0;
  }
};

xwm::Architecture *load_architecture(xwm::Vec<std::string> args) {
  return new MyArchitecture(std::move(args));
}
}