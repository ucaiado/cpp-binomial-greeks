#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#include "files_parser.h"
#include "option_portfolio.h"

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
    }
  }
  return std::move(rtns_paths);
}

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
    }
  }
  final_portfolio.total_rows(ii);
  return std::move(final_portfolio);
}

void DataParser::SaveUnderlyingGreeks(
    Portfolio &this_portfolio, std::vector<std::string> &vec_underlyings) {
  std::ofstream myfile;
  myfile.open(kDataDirectory + kUnderlyingGreeksFilename);
  myfile << "Underlying,PnL,Delta,Gamma,Vega,Theta,Rho\n";
  for (auto &s_undly : vec_underlyings) {
    auto this_underlying = this_portfolio.getUnderlying(s_undly);
    myfile << this_underlying->underlying << ",";
    myfile << this_underlying->pnl << ",";
    myfile << this_underlying->undly_greeks.delta << ",";
    myfile << this_underlying->undly_greeks.gamma << ",";
    myfile << this_underlying->undly_greeks.vega << ",";
    myfile << this_underlying->undly_greeks.theta << ",";
    myfile << this_underlying->undly_greeks.rho << "\n";
  }

  myfile.close();
}

void DataParser::SaveOptionGreeks(Portfolio &this_portfolio,
                                  std::vector<std::string> &vec_underlyings) {
  std::ofstream myfile;
  myfile.open(kDataDirectory + kPortfolioGreeksFilename);
  myfile << "Underlying,Instrument,PnL,Delta,Gamma,Vega,Theta,Rho\n";
  for (auto &s_undly : vec_underlyings) {
    auto this_underlying = this_portfolio.getUnderlying(s_undly);
    for (auto &this_instr : this_underlying->undly_positions) {
      myfile << this_instr.underlying << ",";
      myfile << this_instr.symbol << ",";
      myfile << this_instr.pnl << ",";
      myfile << this_instr.option_greeks.delta * this_instr.quantity << ",";
      myfile << this_instr.option_greeks.gamma * this_instr.quantity << ",";
      myfile << this_instr.option_greeks.vega * this_instr.quantity << ",";
      myfile << this_instr.option_greeks.theta * this_instr.quantity << ",";
      myfile << this_instr.option_greeks.rho * this_instr.quantity << "\n";
    }
  }

  myfile.close();
}
