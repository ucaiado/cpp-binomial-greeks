#include "files_parser.h"
#include "pricing.h"
#include <algorithm>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

int main() {

  std::cout << "\n====== OPTION PORTFOLIO SUMMARY ======"
            << "\n";

  // Load portfolio and recover underlying list
  auto portfolio = DataParser::LoadPortfolio();
  std::cout << "... number of instrument objects created: "
            << portfolio.number_of_instruments() << "\n";

  auto vec_underlyings = portfolio.getUnderlyingsList();
  std::cout << "... there are " << vec_underlyings.size()
            << " underlyings in the list recovered \n";

  // calulate the option Greeks and consolidate the data
  float f_tpnl = 0;
  std::vector<std::future<void>> futures;
  for (auto &s_undly : vec_underlyings) {
    auto this_underlying = portfolio.getUnderlying(s_undly);
    futures.emplace_back(std::async(std::launch::async,
                                    &Pricing::compute_udly_greeks,
                                    this_underlying, 20));
    std::cout << "   => start thread to " << this_underlying->underlying
              << "\n";
  }

  for (auto &ftr : futures) {
    ftr.wait();
  }

  for (auto &s_undly : vec_underlyings) {
    auto this_underlying = portfolio.getUnderlying(s_undly);
    f_tpnl += this_underlying->pnl;
    std::cout << "   There are " << this_underlying->undly_positions.size()
              << " instruments linked to " << this_underlying->underlying
              << " and the current pnl is " << this_underlying->pnl << "\n";
  }

  std::cout << "... the current pnl of this portfolio is " << f_tpnl << "\n";

  // save data to files
  std::cout << "... creating files "
            << "\n";
  DataParser::SaveUnderlyingGreeks(portfolio, vec_underlyings);
  DataParser::SaveOptionGreeks(portfolio, vec_underlyings);

  return 0;
}
