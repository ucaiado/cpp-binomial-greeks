#ifndef OPTION_PORTFOLIO_H
#define OPTION_PORTFOLIO_H

#include <string>

namespace Options {
// Option Type. Can be call or put
enum OptionType { CALL, PUTT };

// Option Style. Can be American or Europian
enum OptionStyle { AMER, EURO };
}; // namespace Options

namespace Portfolio {

// Instrument Type. Can be stock or option
enum InstrumentType { STOCK, OPTION };

/**
 * Data holder to the instrument paramters from portfolio
 *
 * @param underlying. Name of the underlying/stock
 * @param underlying_id.  underlying ID
 * @param symbol. Name of the instrument
 * @param quantity. Name of the instrument
 * @param price. Price paid for the instrument
 * @param volume. Volume transitioned in the instrument
 * @param S. Value of the underlying, if option, or of the instrument, if stock
 * @param K. Strike of the option, if it is the case
 * @param r. Current free risk rate, if it is the case
 * @param T. Time to expiration, in days, if it is the case
 * @param vol. volatility on what the option is based, if it is the case
 * @param instrument_type. InstrumentType object.
 * @param option_type. OptionType object.
 * @param option_style. OptionStyle object.
 * @param H1.
 */
struct PortfolioParams {
  InstrumentType instrument_type; // Type
  std::string underlying;         // Underlying
  int underlying_id;              // UnderlyingID
  std::string symbol;             // Instrument
  float quantity;                 // Qty
  float price;                    // Price
  float volume;                   // Volume
  float T;                        // Wrd
  float K;                        // Strike
  float S;                        // S
  float r;
  float vol;                         // ImpVol
  Options::OptionType option_type;   // OptnTp
  Options::OptionStyle option_style; // OptnStyle
  float H1;
};

/**
 * Data holder to portion of portfolio related to a specific underlying
 *
 * @param underlying. Name of the underlying
 * @param underlying_id. underlying ID
 * @param undly_portfolio. A vector of instruments related to this underlying
 * @param undly_paths. A vector of random paths related to this underlying
 */
struct UnderlyingPortfolio {
  std::string underlying; // Underlying
  int underlying_id;      // UnderlyingID
  std::string bla;        // Instrument
  std::vector<PortfolioParams> undly_portfolio;
  std::vector<std::vector<float>> undly_paths;
};

}; // namespace Portfolio

#endif
