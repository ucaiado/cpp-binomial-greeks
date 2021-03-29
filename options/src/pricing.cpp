#include <cmath>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "option_portfolio.h"
#include "pricing.h"

/* Implementation Pricing functions */

float Pricing::fixed_mc(Instrument::Params &instr,
                        std::vector<std::vector<float>> underlying_paths) {
  float f_price = 0.0;
  float f_num_simulations = underlying_paths.size();
  std::cout << f_num_simulations << std::endl;

  float multiplierCallPut = 1.0;
  if (instr.option_type == Options::Type::PUT) {
    multiplierCallPut = -1.0;
  }

  float sumC0 = 0.0, sumC02 = 0.0, std_dev = 0.0, dt = 1.0;

  float f_current_rtn = 0.0;
  for (auto &this_paths : underlying_paths) {
    float f_steps = 0;
    for (auto &f_this_rtn : this_paths) {
      if (instr.T - f_steps < -1e-6) {
        break;
      }
      f_current_rtn = f_this_rtn;
      std::cout << instr.T << f_steps << std::endl;
      ++f_steps;
    }
    float ST = exp(f_current_rtn * instr.S);
    float CT = 0.0;

    CT = Options::Max(multiplierCallPut * (ST - instr.K), 0);
    float C0 = exp(-instr.r * dt) * CT;
    sumC0 += C0;
    sumC02 += (C0 * C0);
  }

  f_price = sumC0 / f_num_simulations;

  return f_price;
}

float Pricing::binomialtree(Instrument::Params &instr, int i_num_steps) {
  // set the binomial tree params
  float dt = instr.T / 252.0 / i_num_steps;
  float u = exp(instr.vol * sqrt(dt));
  float d = 1.0 / u;
  float p = (exp(instr.r * dt) - d) / (u - d);
  float f_multCallPut = 1.0;
  if (instr.option_type == Options::Type::PUT) {
    f_multCallPut = -1.0;
  }

  // initiate tree vector
  std::vector<float> vec_tree(i_num_steps, 0.0);

  for (int ii = i_num_steps; ii >= 0; ii--) {
    for (int jj = 0; jj < ii + 1; jj++) {
      float f_asset_price = instr.S * pow(u, ii - jj) * pow(d, jj);
      float f_intr_value =
          Options::Max(f_multCallPut * (f_asset_price - instr.K), 0);
      if (ii == i_num_steps) {
        // calculate payoff
        vec_tree[jj] = f_intr_value;
      } else {
        vec_tree[jj] = p * vec_tree[jj] + (1.0 - p) * vec_tree[jj + 1];
        vec_tree[jj] *= exp(-instr.r * dt);

        if (instr.option_style == Options::Style::AMER) {
          if (vec_tree[jj] < f_intr_value) {
            vec_tree[jj] = f_intr_value;
          }
        }
      }
    }
  }

  return vec_tree[0];
}

float Pricing::binomialdelta(Instrument::Params instr, int i_num_steps) {

  // check if it is a stock
  if (instr.type == Instrument::Type::STOCK) {
    return 1.0;
  }

  // get the price  with the current value of S
  float f_price1 = binomialtree(instr, i_num_steps);

  // save the current value and increment it by 0.1%
  float f_temp = instr.S;
  instr.S *= (1 + 0.001);

  // get the price  with the incremented value of S
  float f_price2 = binomialtree(instr, i_num_steps);

  // set the value to the original one
  instr.S = f_temp;

  // compute the delta numerically. the unit is dimensionless
  float f_delta = (f_price2 - f_price1) / (0.001 * instr.S);

  // change unit to exposure in brl
  // f_delta *= instr.S

  return f_delta;
}

float Pricing::binomialgamma(Instrument::Params instr, int i_num_steps) {

  // check if it is a stock
  if (instr.type == Instrument::Type::STOCK) {
    return 0.0;
  }

  // get the price  with the current value of S
  float f_price1 = binomialtree(instr, i_num_steps);

  // save the current value and increment it by 0.1%
  float f_temp = instr.S;
  instr.S *= (1 + 0.001);

  // get the price  with the incremented value of S
  float f_price2 = binomialtree(instr, i_num_steps);

  // decrement the current value by 0.1%
  instr.S = f_temp * (1 - 0.001);

  // get the price  with the decremented value of S
  float f_price3 = binomialtree(instr, i_num_steps);

  // set the value to the original one
  instr.S = f_temp;

  // compute the gamma numerically. the unit is 1 / brl
  float f_gamma =
      (f_price2 - 2 * f_price1 + f_price3) / pow((0.001 * instr.S), 2);

  // change unit to how much long/short more it gets / 1% in S
  f_gamma /= (1.0 / instr.S);

  return f_gamma;
}

float Pricing::binomialtheta(Instrument::Params instr, int i_num_steps) {

  // check if it is a stock
  if (instr.type == Instrument::Type::STOCK) {
    return 0.0;
  }

  // get the price  with the current expiration of the option
  float f_price1 = binomialtree(instr, i_num_steps);

  // save the current value and increment it by 0.1%
  float f_temp = instr.T;
  instr.T += 1.0;

  // get the price  with the incremented expiration of the option
  float f_price2 = binomialtree(instr, i_num_steps);

  // set the value to the original one
  instr.T = f_temp;

  // compute the theta numerically. the unit is brl / day
  float f_theta = (f_price2 - f_price1) / 1.0;

  return f_theta;
}

float Pricing::binomialvega(Instrument::Params instr, int i_num_steps) {

  // check if it is a stock
  if (instr.type == Instrument::Type::STOCK) {
    return 0.0;
  }

  // get the price  with the current volatility of the option
  float f_price1 = binomialtree(instr, i_num_steps);

  // save the current value and increment it by 0.1%
  float f_temp = instr.vol;
  instr.vol *= (1 + 0.01);

  // get the price  with the incremented volatility of the option
  float f_price2 = binomialtree(instr, i_num_steps);

  // set the value to the original one
  instr.vol = f_temp;

  // compute the vega numerically. the unit is brl / % in vol
  float f_vega = (f_price2 - f_price1) / (0.01 * instr.vol * 100);

  return f_vega;
}

float Pricing::binomialrho(Instrument::Params instr, int i_num_steps) {

  // check if it is a stock
  if (instr.type == Instrument::Type::STOCK) {
    return 0.0;
  }

  // get the price  with the current interest rate
  float f_price1 = binomialtree(instr, i_num_steps);

  // save the current value and increment it by 0.1%
  float f_temp = instr.r;
  instr.r *= (1 + 0.001);

  // get the price  with the incremented interest rate
  float f_price2 = binomialtree(instr, i_num_steps);

  // set the value to the original one
  instr.r = f_temp;

  // compute the rho numerically. the unit is brl / % in interest rate
  float f_rho = (f_price2 - f_price1) / (0.001 * instr.r * 100);

  return f_rho;
}

void Pricing::compute_option_greeks(Instrument::Params &instr,
                                    int i_num_steps) {
  // compute values and fill in the required data structure
  instr.theorical_price = Pricing::binomialtree(instr, i_num_steps);
  instr.option_greeks.delta = Pricing::binomialdelta(instr, i_num_steps);
  instr.option_greeks.gamma = Pricing::binomialgamma(instr, i_num_steps);
  instr.option_greeks.theta = Pricing::binomialtheta(instr, i_num_steps);
  instr.option_greeks.vega = Pricing::binomialvega(instr, i_num_steps);
  instr.option_greeks.rho = Pricing::binomialrho(instr, i_num_steps);
  instr.pnl = 0.0;
  if (instr.quantity == 0) {
    instr.pnl = instr.volume;
  } else {
    instr.pnl = (instr.theorical_price - instr.price) * instr.quantity;
  }
}

void Pricing::compute_udly_greeks(std::shared_ptr<UnderlyingParams> &udly,
                                  int i_num_steps) {
  // initialize values
  udly->undly_greeks.delta = 0.0;
  udly->undly_greeks.gamma = 0.0;
  udly->undly_greeks.theta = 0.0;
  udly->undly_greeks.vega = 0.0;
  udly->undly_greeks.rho = 0.0;
  udly->pnl = 0.0;

  // compute values and fill in the required data structure
  for (auto &this_instr : udly->undly_positions) {
    Pricing::compute_option_greeks(this_instr, i_num_steps);
    // delta:= Delta_pos = Q_s + ∑ Δ_i x Q_i
    float f_posdelta = this_instr.option_greeks.delta * this_instr.quantity;
    udly->undly_greeks.delta += f_posdelta;

    // gamma:= Gamma_pos = ∑ Γ_i x Q_i
    float f_posgamma = this_instr.option_greeks.gamma * this_instr.quantity;
    udly->undly_greeks.gamma += f_posgamma;

    // theta:= Theta_pos = ∑ θ_i x Q_i
    float f_postheta = this_instr.option_greeks.theta * this_instr.quantity;
    udly->undly_greeks.theta += f_postheta;

    // vega:= Vega_pos = ∑ ν_i x Q_i
    float f_posvega = this_instr.option_greeks.vega * this_instr.quantity;
    udly->undly_greeks.vega += f_posgamma;

    // rho:= Rho_pos = ∑ ρ_i x Q_i
    float f_posrho = this_instr.option_greeks.rho * this_instr.quantity;
    udly->undly_greeks.rho += f_posrho;

    // pnl:= pnl_pos = ∑ PnL_i
    udly->pnl += this_instr.pnl;
  }
}
