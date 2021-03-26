#include <iostream>
#include "files_parser.h"

int main() {

  auto this_paths = DataParser::LoadPaths("PETR4");

  std::cout << "All working on LoadPaths! " << this_paths[43][999] << "\n";


  auto this_portfolio = DataParser::LoadPortfolio();

  std::cout << "All working on LoadPortfolio! " << this_portfolio.size() << "\n";
  std::cout << "All working on LoadPortfolio! " << this_portfolio[37].underlying << "\n";
  std::cout << "All working on LoadPortfolio! " << this_portfolio[37].underlying_id << "\n";
  return 0;
}
