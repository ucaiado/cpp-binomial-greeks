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

    auto vec_underlyings = portfolio.getUnderlyingsList();
    std::cout << "There are " << vec_underlyings.size() << " underlyings in the list recovered and the last one is " << vec_underlyings.back() << "\n";

    auto this_underlying = portfolio.getUnderlying("PETR4");
    std::cout << "Number of instruments on PETR4: " << this_underlying->undly_positions.size() << "\n";

    auto this_instrument = this_underlying->undly_positions.back();
    std::cout << "last instrument from PETR4: " << this_instrument.symbol << "\n";

    float f_price = Pricing::binomialtree(this_instrument, 20);
    std::cout << "the binomial price for " << this_instrument.symbol << " is " << f_price << "\n";

    float f_delta = Pricing::binomialdelta(this_instrument, 20);
    std::cout << "the binomial delta for " << this_instrument.symbol << " is " << f_delta << "\n";

    float f_gamma = Pricing::binomialgamma(this_instrument, 20);
    std::cout << "the binomial gamma for " << this_instrument.symbol << " is " << f_gamma << "\n";

    float f_theta = Pricing::binomialtheta(this_instrument, 20);
    std::cout << "the binomial theta for " << this_instrument.symbol << " is " << f_theta << "\n";

    float f_vega = Pricing::binomialvega(this_instrument, 20);
    std::cout << "the binomial vega for " << this_instrument.symbol << " is " << f_vega << "\n";

    float f_rho = Pricing::binomialrho(this_instrument, 20);
    std::cout << "the binomial rho for " << this_instrument.symbol << " is " << f_rho << "\n";

    Pricing::compute_option_greeks(this_instrument, 20);
    std::cout << "the delta using compute_option_greeks for " << this_instrument.symbol << " is " << this_instrument.option_greeks.delta << "\n";

    Pricing::compute_udly_greeks(this_underlying, 20);
    auto other_instrument = this_underlying->undly_positions.back();
    std::cout << "the delta using compute_udly_greeks for " << other_instrument.symbol << " is " << other_instrument.option_greeks.delta << "\n";

    std::cout << "current delta for all " << this_underlying->underlying << " options is " << this_underlying->pnl << "\n";
    std::cout << "current pnl for all " << this_underlying->underlying << " options is " << this_underlying->undly_greeks.delta << "\n";
    return 0;
}
