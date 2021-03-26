#ifndef OPTION_PORTFOLIO_H
#define OPTION_PORTFOLIO_H

#include <string>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Options {
// Option Type. Can be call or put
enum Type { CALL, PUTT };

// Option Style. Can be American or Europian
enum Style { AMER, EURO };
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
 * @param H1.
 */
struct Params {
  Type type;              // Type
  std::string underlying; // Underlying
  int underlying_id;      // UnderlyingID
  std::string symbol;     // Instrument
  float quantity;         // Qty
  float price;            // Price
  float volume;           // Volume
  float T;                // Wrd
  float K;                // Strike
  float S;                // S
  float r;
  float vol;                   // ImpVol
  Options::Type option_type;   // OptnTp
  Options::Style option_style; // OptnStyle
  float H1;
};
}; // namespace Instrument

/**
 * Data holder to portion of portfolio related to a specific underlying
 *
 * @param underlying. Name of the underlying
 * @param underlying_id. underlying ID
 * @param undly_portfolio. A vector of instruments related to this underlying
 * @param undly_paths. A vector of random paths related to this underlying
 */
struct UnderlyingParams {
  std::string underlying; // Underlying
  int underlying_id;      // UnderlyingID
  std::string bla;        // Instrument
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
