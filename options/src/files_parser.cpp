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
std::unordered_map<std::string, Portfolio::UnderlyingPortfolio> DataParser::LoadPortfolio() {
  std::vector<Portfolio::UnderlyingPortfolio> portfolio_undlying;
  std::unordered_map<std::string, Portfolio::UnderlyingPortfolio>
      portfolio_undlying2;
  std::string line;
  std::ifstream stream(kDataDirectory + kPortfolioFilename);
  int ii = 0;
  char c;
  if (stream.is_open()) {
    // read just the first line of the file
    while (std::getline(stream, line)) {

      std::istringstream this_row(line);
      int jj = 0;
      if (ii > 0) {
        // Type,Underlying,Instrument,Qty,Price,Volume,Wrd,Strike,OptnStyle,OptnTp,S,ImpVol,UnderlyingID
        // option,B3SA3,B3SAD540,100.0,2.53,-252.99999999999997,20.0,53.66,AMER,CALL,55.9,0.3675,0
        Portfolio::UnderlyingPortfolio this_underlying;
        std::string this_object;
        std:string s_key;
        while (std::getline(this_row, this_object, ',')) {
          if (jj == 1) {
            std::cout << "map count of underlying: "
                      << portfolio_undlying2.count(this_object) << "\n";
            this_underlying.underlying = this_object;
            if (portfolio_undlying2.count(this_object) == 0) {
              portfolio_undlying2.insert({this_object, this_underlying});
            }
            s_key = this_object;
            this_underlying.underlying = this_object;
          } else if (jj == 12) {
            portfolio_undlying[s_key].underlying_id = std::stoi(this_object);
          }

          // std::string underlying;  // Underlying
          // int underlying_id;  // UnderlyingID
          // std::vector<PortfolioParams> undly_portfolio;
          // std::vector<std::vector<float>> undly_paths;

          // // filling Type
          // this_underlying.instrument_type = Portfolio::InstrumentType.OPTION
          // if (Type == 'stock') {
          //   this_underlying.instrument_type  =
          //   Portfolio::InstrumentType.STOCK
          // };
          // // filling Type
          ++jj;
        }
        portfolio_undlying.emplace_back(this_underlying);
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
  return std::move(portfolio_undlying2);
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
