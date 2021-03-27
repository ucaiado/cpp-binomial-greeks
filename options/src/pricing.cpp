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

  float sumC0 = 0.0, sumC02 = 0.0, std_dev = 0.0, dt=1.0;

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


float Pricing::binomialtree(Instrument::Params &instr, int i_num_steps)
{
  // set the binomial tree params
  float dt = instr.T / 252.0 / i_num_steps;
  float u = exp(instr.vol * sqrt(dt));
  float d = 1.0 / u;
  float p = (exp(instr.r * dt) - d) / (u - d);
  float f_multCallPut = 1.0;
  if(instr.option_type == Options::Type::PUT)
  {
    f_multCallPut = -1.0;
  }

  // initiate tree vector
  std::vector<float> vec_tree (i_num_steps, 0.0);

  for(int ii=i_num_steps;ii>=0;ii--)
  {
    for(int jj=0;jj<ii+1;jj++)
    {
      float f_asset_price = instr.S * pow(u, ii-jj) * pow(d, jj);
      float f_intr_value = Options::Max(f_multCallPut * (f_asset_price - instr.K), 0);
      if(ii==i_num_steps)
      {
        // calculate payoff
        vec_tree[jj] = f_intr_value;
      }
      else
      {
        vec_tree[jj] = p * vec_tree[jj] + (1.0 - p) * vec_tree[jj+1];
        vec_tree[jj] *= exp(-instr.r * dt);

        if(instr.option_style == Options::Style::AMER)
        {
          if(vec_tree[jj] < f_intr_value)
          {
            vec_tree[jj] = f_intr_value;
          }
        }
      }
    }
  }

  return vec_tree[0];
}
