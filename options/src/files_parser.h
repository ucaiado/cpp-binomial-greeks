#ifndef FILES_PARSER_H
#define FILES_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>

#include "option_portfolio.h"

namespace DataParser {
// Paths
const std::string kDataDirectory{"../data/"};
const std::string kPortfolioFilename{"portfolio.csv"};
const std::string kUnderlyingGreeksFilename{"out_udlygreeks.csv"};
const std::string kPortfolioGreeksFilename{"out_portgreeks.csv"};

/**
 * Load data from already generated simulations in a vector
 *
 * @param values Container whose values are summed.
 * @return vector of vectors of floar with the return paths.
 */
std::vector<std::vector<float>> LoadPaths(std::string s_asset);

/**
 * Load data from portfolio file in a vector
 *
 * @return vector of UnderlyingPortfolio.
 */
Portfolio LoadPortfolio();

/**
 * Save data related to Underlying positions
 */
void SaveUnderlyingGreeks(Portfolio &this_portfolio,
                          std::vector<std::string> &vec_underlyings);

/**
 * Save data related to option positions
 */
void SaveOptionGreeks(Portfolio &this_portfolio,
                      std::vector<std::string> &vec_underlyings);

}; // namespace DataParser

#endif
