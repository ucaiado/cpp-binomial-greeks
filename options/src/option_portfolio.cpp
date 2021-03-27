#include <cmath>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "option_portfolio.h"

/* Implementation Option functions */
double Options::Max(double a, double b) {
  if (a > b) {
    return a;
  }

  return b;
}

/* Implementation of class "Portfolio" */

Portfolio::Portfolio() {}

void Portfolio::total_rows(int i_size) { _total_rows = i_size - 1; }

int Portfolio::total_rows() { return _total_rows; }

int Portfolio::number_of_instruments() {
  int i_size = 0;
  for (auto &this_pair : _undly_portfolio) {
    i_size += this_pair.second->undly_positions.size();
  }
  return i_size;
}

std::shared_ptr<UnderlyingParams> Portfolio::getUnderlying(std::string s_udly) {
  if (_undly_portfolio.count(s_udly) == 0) {
    return nullptr;
  }
  return _undly_portfolio[s_udly];
  ;
}

// Type,Underlying,Instrument,Qty,Price,Volume,Wrd,Strike,OptnStyle,OptnTp,S,ImpVol,UnderlyingID
// option,B3SA3,B3SAD540,100.0,2.53,-252.99999999999997,20.0,53.66,AMER,CALL,55.9,0.3675,0
void Portfolio::useCellValue(Instrument::Params &instr, std::string &this_cell,
                             int &i_col) {
  if (i_col == 0) {
    // process Instrument Type
    instr.type = Instrument::Type::OPTION;
    if (this_cell == "stock") {
      instr.type = Instrument::Type::STOCK;
    }
  } else if (i_col == 1) {
    // process Underlying name
    instr.underlying = this_cell;
    // initialize the underlying portfolio
    if (_undly_portfolio.count(this_cell) == 0) {
      std::shared_ptr<UnderlyingParams> this_underlying(new UnderlyingParams);
      this_underlying->underlying = this_cell;
      _undly_portfolio.insert({this_cell, std::move(this_underlying)});
    }
  } else if (i_col == 2) {
    // process Symbol name
    instr.symbol = this_cell;
  } else if (i_col == 3) {
    // process Qty
    instr.quantity = std::stoi(this_cell);
  } else if (i_col == 4) {
    // process Price
    instr.price = std::stof(this_cell);
  } else if (i_col == 5) {
    // process Volume
    instr.volume = std::stof(this_cell);
  } else if (instr.type == Instrument::Type::OPTION) {
    if (i_col == 6) {
      // process Wrd
      instr.T = std::stof(this_cell);
    } else if (i_col == 7) {
      // process Strike
      instr.K = std::stof(this_cell);
    } else if (i_col == 8) {
      // process OptnStyle
      instr.option_style = Options::Style::AMER;
      if (this_cell == "EURO") {
        instr.option_style = Options::Style::EURO;
      }
    } else if (i_col == 9) {
      // process OptnTp
      instr.option_type = Options::Type::CALL;
      if (this_cell == "PUTT") {
        instr.option_type = Options::Type::PUT;
      }
    } else if (i_col == 11) {
      // process ImpVol
      instr.vol = std::stof(this_cell);
    }
  } else if (i_col == 10) {
    // process S
    instr.S = std::stof(this_cell);
  } else if (i_col == 12) {
    std::string s_undly = instr.underlying;
    _undly_portfolio[s_undly]->underlying_id = std::stoi(this_cell);
  }
}

void Portfolio::addInstrument2UnderlyingPositions(Instrument::Params &instr) {
  // std::cout << "instr.symbol " << instr.symbol << std::endl;
  _undly_portfolio[instr.underlying]->undly_positions.emplace_back(instr);
}
