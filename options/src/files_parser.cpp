#include <dirent.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#include "files_parser.h"
#include "option_portfolio.h"

/**
 * Load data from already generated simulations in a vector
 *
 * @param values Container whose values are summed.
 * @return vector of vectors of floats with the return paths.
 */
std::vector<std::vector<float>> DataParser::LoadPaths(std::string s_asset) {
  std::vector<std::vector<float>> rtns_paths;
  std::string line;
  std::ifstream stream(kDataDirectory + s_asset + ".csv");
  int ii = 0;
  char c;
  if (stream.is_open()) {
    // read just the first line of the file
    while (std::getline(stream, line)) {
      std::istringstream this_row(line);
      rtns_paths.emplace_back(std::vector<float>());
      float this_value;
      int jj = 0;
      while (this_row >> this_value >> c && c == ',') {
        rtns_paths[ii].emplace_back(this_value);
        ++jj;
      }
      ++ii;
      // std::cout << "next columns # " << ii
      //           << " rows filled # " << jj
      //           << "  rtns_paths[ii-1].back() = " << rtns_paths[ii-1].back()
      //           << "  rtns_paths[ii-1].size() = " << rtns_paths[ii-1].size()
      //           << std::endl;
    }
  }
  return std::move(rtns_paths);
}

/**
 * Load data from portfolio file in a vector
 *
 * @return vector of UnderlyingPortfolio.
 */
Portfolio DataParser::LoadPortfolio() {
  Portfolio final_portfolio;
  std::string line;
  std::ifstream stream(kDataDirectory + kPortfolioFilename);
  int ii = 0;
  if (stream.is_open()) {
    // read just the first line of the file
    while (std::getline(stream, line)) {
      std::istringstream this_row(line);
      int jj = 0;
      if (ii > 0) {
        Instrument::Params this_instrument;
        std::string this_cell;
        while (std::getline(this_row, this_cell, ',')) {
          final_portfolio.useCellValue(this_instrument, this_cell, jj);
          ++jj;
        }
        final_portfolio.addInstrument2UnderlyingPositions(this_instrument);
      }
      ++ii;
      // std::cout << "rows filled # " << ii
      //           << " columns checked # " << jj
      //           << "  portfolio_undlying[ii-1].back() = " <<
      //           portfolio_undlying[ii-1].back()
      //           << "  portfolio_undlying[ii-1].size() = " <<
      //           portfolio_undlying[ii-1].size()
      //           << std::endl;
    }
  }
  final_portfolio.total_rows(ii);
  return std::move(final_portfolio);
}

//  */
// struct PortfolioParams
// {
//   InstrumentType instrument_type;  // Type
//   std::string underlying;  // Underlying
//   int underlying_id;  // UnderlyingID
//   std::string symbol;  // Instrument
//   float quantity;  // Qty
//   float price;  // Price
//   float volume;  // Volume
//   float T;  // Wrd
//   float K;  // Strike
//   float S;  // S
//   float r;
//   float vol;  // ImpVol
//   Options::OptionType option_type;  // OptnTp
//   Options::OptionStyle option_style;  // OptnStyle
//   float H1;
// };
