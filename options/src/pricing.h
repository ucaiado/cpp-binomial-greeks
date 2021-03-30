#ifndef PRICING_H
#define PRICING_H

#include <string>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "option_portfolio.h"

namespace Pricing {

/**
 * Compute option price using the same procedure used by monte carlo pricing,
 * but with paths generated previously. ATENTION: Just use for europian options
 *
 * @param instr. Instrument parameter
 * @param underlying_paths. vector of vectors of floats with the return paths.
 * @return option price
 */
float fixed_mc(Instrument::Params &instr,
               std::vector<std::vector<float>> underlying_paths);

/**
 * Compute option price using a binomial tree. It handles American end Europian
 * options
 *
 * @param instr. Instrument parameter
 * @param num_steps. number of steps to build the tree
 * @return option price
 */
float binomialtree(Instrument::Params &instr, int i_num_steps);

/*
return the aproximated options delta using binomial tree
*/
float binomialdelta(Instrument::Params instr, int i_num_steps);

/*
return the aproximated options gamma using binomial tree
*/
float binomialgamma(Instrument::Params instr, int i_num_steps);

/*
return the aproximated options vega using binomial tree
*/
float binomialvega(Instrument::Params instr, int i_num_steps);

/*
return the aproximated options theta using binomial tree
*/
float binomialtheta(Instrument::Params instr, int i_num_steps);

/*
return the aproximated options rho using binomial tree
*/
float binomialrho(Instrument::Params instr, int i_num_steps);

/*
Fill in option_greeks and pnl private members of the Instrument::Params object
*/
void compute_option_greeks(Instrument::Params &instr, int i_num_steps);

/*
Fill in undly_greeks and pnl private members of the UnderlyingParams object
*/
void compute_udly_greeks(std::shared_ptr<UnderlyingParams> udly,
                         int i_num_steps);

}; // namespace Pricing

#endif
