#include <iostream>
#include "files_parser.h"
#include "pricing.h"

int main() {

  auto this_paths = DataParser::LoadPaths("PETR4");
  auto portfolio = DataParser::LoadPortfolio();

  // Test LoadPaths
  std::cout << "All working on LoadPaths! " << this_paths[20][38] << "\n";
  for (auto &cell : this_paths[43]) {
    std::cout << cell << std::endl;
  }
  std::cout <<  "\n";

  // Test LoadPortfolio
  std::cout << "Number of rows: " << portfolio.total_rows() << "\n";
  std::cout << "Number of instrument objects instanciated: " << portfolio.number_of_instruments() << "\n";

  auto this_underlying = portfolio.getUnderlying("PETR4");
  std::cout << "Number of instruments on PETR4: " << this_underlying->undly_positions.size() << "\n";

  auto this_instrument = this_underlying->undly_positions.back();
  std::cout << "last instrument from PETR4: " << this_instrument.symbol << "\n";

  float f_price = Pricing::binomialtree(this_instrument, 20);
  std::cout << "the price for " << this_instrument.symbol << " is " << f_price << "\n";
  return 0;
}
