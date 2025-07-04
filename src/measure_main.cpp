#include "measurement.hpp"
#include <iostream>
#include <string>

int main(int argc, const char* argv[]) {
  int count = 1;
  try {
    if (argc >= 2) {
      count = std::stoi(argv[1]);
    }
  } catch (std::exception& e) {
    std::cerr << argv[0] << " <count>" << std::endl;
    return 1;
  }
  if (count <= 0) {
    std::cerr << "<count> must be greater than 0" << std::endl;
    return 1;
  }
  ::measurement::Measure::ExecuteAll(count);
}
