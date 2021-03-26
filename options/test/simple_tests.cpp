#include <iostream>
#include "files_parser.h"

int main() {

  auto this_paths = DataParser::LoadPaths("PETR4");
  auto portfolio = DataParser::LoadPortfolio();

  // Test LoadPaths
  std::cout << "All working on LoadPaths! " << this_paths[43][999] << "\n";

  // Test LoadPortfolio
  std::cout << "Number of rows: " << portfolio.total_rows() << "\n";
  std::cout << "Number of instrument objects instanciated: " << portfolio.number_of_instruments() << "\n";

  auto this_underlying = portfolio.getUnderlying("PETR4");
  std::cout << "Number of instruments on PETR4: " << this_underlying->undly_positions.size() << "\n";

  auto this_instrument = this_underlying->undly_positions.back();
  std::cout << "last instrument from PETR4: " << this_instrument.symbol << "\n";
  return 0;
}
