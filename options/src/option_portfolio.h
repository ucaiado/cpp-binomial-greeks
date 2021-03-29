#ifndef OPTION_PORTFOLIO_H
#define OPTION_PORTFOLIO_H

#include <string>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Options {
// Option Type. Can be call or put
enum Type { CALL, PUT };

// Option Style. Can be American or Europian
enum Style { AMER, EURO };

// Option Greeks
struct Greeks {
  float delta;
  float gamma;
  float vega;
  float theta;
  float rho;
};

// Return max between two numbers
double Max(double a, double b);

}; // namespace Options

namespace Instrument {
// Instrument Type. Can be stock or option
enum Type { STOCK, OPTION };

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
 * @param option_greeks. Option Greeks object.
 * @param theorical_price. Theorical price of the option
 * @param pnl. Current pnl of this position
 */
struct Params {
  Type type;                     // Type
  std::string underlying;        // Underlying
  int underlying_id;             // UnderlyingID
  std::string symbol;            // Instrument
  float quantity;                // Qty
  float price;                   // Price
  float volume;                  // Volume
  float T = 9999;                // Wrd
  float K = 0;                   // Strike
  float S;                       // Stock price
  float r = 0.0275;              // interest rate
  float vol;                     // ImpVol
  Options::Type option_type;     // OptnTp
  Options::Style option_style;   // OptnStyle
  Options::Greeks option_greeks; // OptnGreeks
  float theorical_price;         // Price computed by a model
  float pnl;                     // current pnl of this options
};
}; // namespace Instrument

/**
 * Data holder to portion of portfolio related to a specific underlying
 *
 * @param underlying. Name of the underlying
 * @param underlying_id. underlying ID
 * @param undly_portfolio. A vector of instruments related to this underlying
 * @param undly_greeks. Consolidated greeks for this underlying
 */
struct UnderlyingParams {
  std::string underlying;       // Underlying
  int underlying_id;            // UnderlyingID
  std::string bla;              // Instrument
  Options::Greeks undly_greeks; // consolidated OptnGreeks
  float pnl;                    // current pnl of Underlying
  std::vector<Instrument::Params> undly_positions;
};

/**
 * Representation of all positions from a Portfolio, indexed by underlying name
 */
class Portfolio {
public:
  // constructors / destructors
  Portfolio();
  // ~Portfolio();

  // getters / setters
  int total_rows();
  void total_rows(int i_size);
  int number_of_instruments();
  std::vector<std::string> getUnderlyingsList();
  std::shared_ptr<UnderlyingParams> getUnderlying(std::string s_udly);

  // typical behaviour methods
  void addInstrument2UnderlyingPositions(Instrument::Params &instr);

  //   use a cell extract from a row from portfolio.csv file to fill in
  //     informations in a UnderlyingParams or a InstrumentParams object.
  //     this_cell is the cell value and i_col, the column index
  void useCellValue(Instrument::Params &instr, std::string &this_cell,
                    int &i_col);

private:
  // typical behaviour methods

  // private members
  std::unordered_map<std::string, std::shared_ptr<UnderlyingParams>>
      _undly_portfolio;
  int _total_rows = -1;
};

#endif
