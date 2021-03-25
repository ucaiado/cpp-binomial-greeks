#ifndef FILES_PARSER_H
#define FILES_PARSER_H

#include <fstream>
#include <regex>
#include <string>

#include "option_portfolio.h"

namespace DataParser {
// Paths
const std::string kDataDirectory{"../data/"};
const std::string kPortfolioFilename{"portfolio.csv"};

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
std::vector<Portfolio::UnderlyingPortfolio> LoadPortfolio();
};  // namespace DataParser

#endif
