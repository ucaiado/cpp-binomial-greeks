#include <iostream>
#include "files_parser.h"

int main() {

  auto this_data = DataParser::ReturnPaths("PETR4");

  std::cout << "All working 2! " << this_data[43][999] << "\n";
  return 0;
}
