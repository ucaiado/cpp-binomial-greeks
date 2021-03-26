#include "files_parser.h"
#include <iostream>

int main() {

  auto this_paths = DataParser::LoadPaths("PETR4");

  std::cout << "All working on LoadPaths! " << this_paths[43][999] << "\n";

  auto this_portfolio = DataParser::LoadPortfolio();

  return 0;
}
